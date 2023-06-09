[Top]
components : Warehouse@ggad 
out : FacWar_out1 FacWar_out2 
in : Send FacWar_in1 FacWar_in2 
Link : Send Send@Warehouse
Link : FacWar_in1 FacWar_in1@Warehouse
Link : FacWar_in2 FacWar_in2@Warehouse
Link : FacWar_out1@Warehouse FacWar_out1
Link : FacWar_out2@Warehouse FacWar_out2

[Warehouse]
source : Warehouse.cdd


