package main

import (
	"C"
	"fmt"
	"time"

	ffprobe "github.com/vansante/go-ffprobe"
)

//export getDur
func getDur(url *C.char) *C.char {
	d, _ := ffprobe.GetProbeData("D:/a.mp4", 120000*time.Millisecond)
	dur := fmt.Sprintf("%f", d.Format.Duration().Seconds())
	cs := C.CString(dur)
	return cs
}

func main() {
	//pass
}
