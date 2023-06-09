[Top]
components : PowderRoom@ggad PressRoom@ggad BlisterPack@ggad 
out : Busy PMPout 
in : PMPin 
Link : PMPin PMP_in@PowderRoom
Link : Press@PowderRoom Press@PressRoom
Link : Busy1@PowderRoom Busy
Link : BlilsterPack@PressRoom Blister@BlisterPack
Link : PMP_out@BlisterPack PMPout

[PowderRoom]
source : PowderRoomType.cdd

[PressRoom]
source : PressRoomType.cdd

[BlisterPack]
source : blisterPackType.cdd


