[top]
components : FactoryWarehouse@FactoryWarehouse
in : FacWar_in1 FacWar_in2 Send
out : FacWar_out1 FacWar_out2
Link : FacWar_in1 FacWar_in1@FactoryWarehouse
Link : FacWar_in2 FacWar_in2@FactoryWarehouse
Link : Send Send@FactoryWarehouse
Link : FacWar_out1@FactoryWarehouse FacWar_out1
Link : FacWar_out2@FactoryWarehouse FacWar_out2