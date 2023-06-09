[Top]
components : FactoryAdministrator@FactoryAdministrator FactoryWarehouse PMP 
out : out PMP_in FacWar_in2 FacWar_in1 Send FacWar_out1 FacWar_out2
in : OrderInfo2 RawMaterials2 
Link : out@PMP PMP_out@FactoryAdministrator
Link : PMP_in@FactoryAdministrator in@PMP
Link : PMP_in@FactoryAdministrator PMP_in
Link : Busy@PMP Busy1@FactoryAdministrator
Link : OrderInfo2 OrderInfo2@FactoryAdministrator
Link : RawMaterials2 RawMaterials2@FactoryAdministrator
Link : FacWar_in2@FactoryAdministrator FacWar_in2@FactoryWarehouse
Link : FacWar_in1@FactoryAdministrator FacWar_in1@FactoryWarehouse
Link : FacWar_in2@FactoryAdministrator FacWar_in2
Link : FacWar_in1@FactoryAdministrator FacWar_in1
Link : Send@FactoryAdministrator Send@FactoryWarehouse
Link : Send@FactoryAdministrator Send
Link : FacWar_out1@FactoryWarehouse FacWar_out1@FactoryAdministrator
Link : FacWar_out2@FactoryWarehouse FacWar_out2@FactoryAdministrator
Link : FacWar_out1@FactoryWarehouse FacWar_out1
Link : FacWar_out2@FactoryWarehouse FacWar_out2
Link : FinishedPro1@FactoryAdministrator out

[FactoryAdministrator]

[FactoryWarehouse]
components : Warehouse@ggad
out : FacWar_out1 FacWar_out2
in : FacWar_in1 FacWar_in2 Send
link : FacWar_out2@Warehouse FacWar_out2
link : FacWar_out1@Warehouse FacWar_out1
link : FacWar_in1 FacWar_in1@Warehouse
link : FacWar_in2 FacWar_in2@Warehouse
link : Send Send@Warehouse

[Warehouse]
source : Warehouse.cdd

[PMP]
components : PressRoom@ggad BlisterPack@ggad PowderRoom@ggad 
out : out Busy 
in : in 
Link : in PMP_in@PowderRoom
Link : Press@PowderRoom Press@PressRoom
Link : Busy1@PowderRoom Busy
Link : BlilsterPack@PressRoom Blister@BlisterPack
Link : PMP_out@BlisterPack out

[PressRoom]
source : PressRoomType.cdd

[BlisterPack]
source : blisterPackType.cdd

[PowderRoom]
source : PowderRoomType.cdd
