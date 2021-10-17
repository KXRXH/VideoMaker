package main

/*
#include <stdlib.h>
*/

import (
	"C"
)
import (
	"fmt"
	"time"

	ffprobe "github.com/vansante/go-ffprobe"
)

//export getDur
func getDur(url *C.char) *C.char {
	gourl := C.GoString(url)
	d, _ := ffprobe.GetProbeData(gourl, 120000*time.Millisecond)
	dur := fmt.Sprintf("%f", d.Format.Duration().Seconds())
	return C.CString(dur)
}
func main() {
	// d, _ := ffprobe.GetProbeData("D:/a.mp4", 120000*time.Millisecond)
	// dur := fmt.Sprintf("%f", d.Format.Duration().Seconds())
	// fmt.Println(dur)
}
