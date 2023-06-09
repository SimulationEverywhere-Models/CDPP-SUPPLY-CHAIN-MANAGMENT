[top]
components : packRoom@PackRoom
out : PMP_out Busy4
in : FinalPack
Link : PMP_out@PackRoom PMP_out
Link : FinalPack FinalPack@PackRoom
Link : Busy4@PackRoom Busy4