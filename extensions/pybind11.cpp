#include "nms.h"

PYBIND11_MODULE(nms, m) {
    m.def("nms_cpp", &nms, "nms");
    m.def("iou_cpp", &iou_overlap, "iou overlap");
}