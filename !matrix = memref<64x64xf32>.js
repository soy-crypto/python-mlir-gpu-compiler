!matrix = memref<64x64xf32>
!tile = memref<8x8xf32, #gpu.address_space<workgroup>>

module {
  func.func @gemm(%A: !matrix, %B: !matrix, %C: !matrix) {
    %c0  = arith.constant 0 : index
    %c1  = arith.constant 1 : index
    %c8  = arith.constant 8 : index
    %c64 = arith.constant 64 : index
    %zero = arith.constant 0.0 : f32

    gpu.launch blocks(%bx, %by, %bz) in (%gridX = %c8, %gridY = %c8, %gridZ = %c1) threads(%tx, %ty, %tz) in (%sizeX = %c8, %sizeY = %c8, %sizeZ = %c1) workgroup(%sharedA : !tile, %sharedB : !tile) 
    {
      // 🟦 Each thread owns one C[row, col]. You already emit this.
      %firstRow = arith.muli %by, %sizeY : index
      %row = arith.addi %firstRow, %ty : index
      %firstCol = arith.muli %bx, %sizeX : index
      %col = arith.addi %firstCol, %tx : index

      // 🟨 Outer loop: visit K tiles starting at 0, 8, 16, ..., 56.
      %result = scf.for %kBase = %c0 to %c64 step %c8 iter_args(%acc = %zero) -> (f32) 
      {

        %aCol = arith.addi %kBase, %tx : index
        %bRow = arith.addi %kBase, %ty : index
        %a = memref.load %A[%row, %aCol] : !matrix
        %b = memref.load %B[%bRow, %col] : !matrix
        memref.store %a, %sharedA[%ty, %tx] : !tile
        memref.store %b, %sharedB[%ty, %tx] : !tile
        gpu.barrier

        // 🟩 Inner loop: add 8 products to this thread's running sum.
        %tileSum = scf.for %d = %c0 to %c8 step %c1 iter_args(%sum = %acc) -> (f32) 
        {
          %x = memref.load %sharedA[%ty, %d] : !tile
          %y = memref.load %sharedB[%d, %tx] : !tile
          %product = arith.mulf %x, %y : f32
          %next = arith.addf %sum, %product : f32
          scf.yield %next : f32
        }

        gpu.barrier
        scf.yield %tileSum : f32
      }

      memref.store %result, %C[%row, %col] : !matrix
      gpu.terminator

    }

    return

  }

}