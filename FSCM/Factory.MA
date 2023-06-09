[top]
components : FactoryWarehouse@FactoryWarehouse FactoryAdministrator@FactoryAdministrator PMP
out : FinishedPro1 Send FacWar_in1 FacWar_in2 FacWar_out1 FacWar_out2 PMP_out PMP_in
in : RawMaterials2 OrderInfo2
Link : FinishedPro1@FactoryAdministrator FinishedPro1
Link : RawMaterials2 RawMaterials2@FactoryAdministrator
Link : OrderInfo2 OrderInfo2@FactoryAdministrator
Link : Send@FactoryAdministrator Send@FactoryWarehouse
Link : FacWar_in1@FactoryAdministrator FacWar_in1@FactoryWarehouse
Link : FacWar_in2@FactoryAdministrator FacWar_in2@FactoryWarehouse
Link : FacWar_out1@FactoryWarehouse FacWar_out1@FactoryAdministrator
Link : FacWar_out2@FactoryWarehouse FacWar_out2@FactoryAdministrator
Link : PMP_out@PMP PMP_out@FactoryAdministrator
Link : Busy1@PMP Busy1@FactoryAdministrator
Link : PMP_in@FactoryAdministrator PMP_in@PMP
Link : Send@FactoryAdministrator Send
Link : FacWar_in1@FactoryAdministrator FacWar_in1
Link : FacWar_in2@FactoryAdministrator FacWar_in2
Link : FacWar_out1@FactoryWarehouse FacWar_out1
Link : FacWar_out2@FactoryWarehouse FacWar_out2
Link : PMP_out@PMP PMP_out
Link : PMP_in@FactoryAdministrator PMP_in

[PMP]
components : powderRoom@PowderRoom pressRoom@PressRoom blisterRoom@BlisterRoom packRoom@PackRoom
out : PMP_out Busy1
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