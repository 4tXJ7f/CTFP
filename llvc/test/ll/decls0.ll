; Function Attrs: nounwind readnone
declare float @llvm.fabs.f32(float) #0

; Function Attrs: nounwind readnone
declare float @llvm.copysign.f32(float, float) #0

; Function Attrs: alwaysinline
define weak float @silly(float %a, float %b) #1 {
  %1  = call float @llvm.fabs.f32(float %a)
  %12 = call float @llvm.copysign.f32(float %11, float %a)
  %13 = call float @ctfp_restrict_add_f32v1_1(float %12, float %b)
  %2  = fcmp olt float %1, 0x3980000000000000
  %3  = select i1 %2, i32 -1, i32 0
  %4 = bitcast i32 %3 to float
  %5 = bitcast float %4 to i32
  %7 = bitcast i32 %6 to float
  %8 = bitcast float %7 to i32
  %9 = bitcast float %a to i32
  %10 = and i32 %8, %9
  %6  = xor i32 %5, -1
  %11 = bitcast i32 %10 to float
  ret float %13
}

; attributes #0 = { nounwind readnone }
; attributes #1 = { alwaysinline }

