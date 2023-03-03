#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <pybind11/stl.h>
#include <pybind11/pybind11.h>

std::vector<std::vector<double> > nms(std::vector<std::vector<double> >& dt_bboxes);

double iou_overlap(std::vector<double>& bbox1, std::vector<double>& bbox2);