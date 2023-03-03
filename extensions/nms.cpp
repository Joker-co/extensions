#include "nms.h"

double iou_overlap(std::vector<double>& bbox1, std::vector<double>& bbox2) {
    double x11 = bbox1[0], y11 = bbox1[1], x12 = bbox1[2], y12 = bbox1[3];
    double x21 = bbox2[0], y21 = bbox2[1], x22 = bbox2[2], y22 = bbox2[3];
    double area1 = (x12 - x11) * (y12 - y11);
    double area2 = (x22 - x21) * (y22 - y21);
    // std::cout << area1 << std::endl;
    // std::cout << area2 << std::endl;

    double xx1 = std::max(x11, x21);
    double yy1 = std::max(y11, y21);
    double xx2 = std::min(x12, x22);
    double yy2 = std::min(y12, y22);
    double width = std::max(xx2 - xx1, (double)0);
    double height = std::max(yy2 - yy1, (double)0);
    double area_inter = width * height;
    // std::cout << area_inter << std::endl;

    return area_inter / (area1 + area2 - area_inter);
}

std::vector<std::vector<double> > nms(std::vector<std::vector<double> >& dt_bboxes) {
    std::vector<std::vector<double> > dt_results;
    int num_dts = dt_bboxes.size();
    int dim_dt = dt_bboxes[0].size();
    std::vector<bool> valid_dts(num_dts, false);
    int num_press = 0;
    // std::cout << "1" << std::endl;

    // open txt file to save iou
    // std::ofstream iou_txt;
    // iou_txt.open("iou_overlaps.txt", std::ios::out | std::ios::app);

    for (int idx_dt = 0; idx_dt < num_dts; idx_dt++) {
        if (valid_dts[idx_dt] == true) {
            continue;
        }
        std::vector<double> top_bbox = dt_bboxes[idx_dt];
        for (int sub_idx = idx_dt + 1; sub_idx < num_dts; sub_idx++) {
            if (valid_dts[sub_idx] == true) {
                continue;
            }
            std::vector<double> sub_bbox = dt_bboxes[sub_idx];
            // calculate iou
            double iou = iou_overlap(top_bbox, sub_bbox);
            // iou_txt << iou << " ";

            // std::cout << "iou: " << iou << std::endl;
            if (iou >= 0.5) {
                num_press += 1;
                valid_dts[sub_idx] = true;
            }
        }
    }
    // std::cout << "2" << std::endl;

    for (int idx = 0; idx < num_dts; idx++) {
        if (valid_dts[idx] == true) {
            // std::cout << "skip" << std::endl;
            continue;
        }
        dt_results.push_back(dt_bboxes[idx]);
    }
    // std::cout << "3" << std::endl;
    // std::cout << "num_press: " << num_press << std::endl;

    return dt_results;
}

void display(std::vector<std::vector<double> >& dt_bboxes) {
    for (int i = 0; i < dt_bboxes.size(); i++) {
        for (int j = 0; j < dt_bboxes[0].size(); j++) {
            std::cout << dt_bboxes[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    std::cout << "NMS .cpp" << std::endl;

    // generate fake dt_bboxes
    std::vector<std::vector<double> > dt_bboxes{{100, 100, 200, 200},{110, 110, 220, 220},{300, 300, 500, 500},{310, 310, 520, 520}};
    std::vector<std::vector<double> > dt_results;
    dt_results = nms(dt_bboxes);
    display(dt_results);
    return 0;
}