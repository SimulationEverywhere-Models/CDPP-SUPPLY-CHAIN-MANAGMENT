[top]
components : powderRoom@PowderRoom pressRoom@PressRoom blisterRoom@BlisterRoom packRoom@PackRoom
out : PMP_out Busy1 Press Busy2 Blister Busy3 FinalPack Busy4
in : PMP_in
Link : PMP_in PMP_in@PowderRoom
Link : Busy1@PowderRoom Busy1
Link : PMP_out@PackRoom PMP_out
Link : Press@PowderRoom Press@PressRoom
Link : Busy2@PressRoom Busy2@PowderRoom
Link : Blister@PressRoom Blister@BlisterRoom
Link : Busy3@BlisterRoom Busy3@PressRoom
Link : FinalPack@BlisterRoom FinalPack@PackRoom
Link : Busy4@PackRoom Busy4@BlisterRoom 

Link : Press@PowderRoom Press
Link : Busy2@PressRoom Busy2
Link : Blister@PressRoom Blister
Link : Busy3@BlisterRoom Busy3
Link : FinalPack@BlisterRoom FinalPack
Link : Busy4@PackRoom Busy4 