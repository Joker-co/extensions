import time
import copy
import numpy as np
from extensions.nms import nms_cpp, iou_cpp


np.random.seed(1)

def iou_overlap(bbox1, bbox2):
    area1 = (bbox1[2] - bbox1[0]) * (bbox1[3] - bbox1[1])
    area2 = (bbox2[2] - bbox2[0]) * (bbox2[3] - bbox2[1])

    xx1 = np.maximum(bbox1[0], bbox2[0])
    yy1 = np.maximum(bbox1[1], bbox2[1])
    xx2 = np.minimum(bbox1[2], bbox2[2])
    yy2 = np.minimum(bbox1[3], bbox2[3])
    width = np.maximum((xx2 - xx1), 0)
    height = np.maximum((yy2 - yy1), 0)
    inter = width * height
    return inter / (area1 + area2 - inter)


def nms(dt_bboxes, iou_thresh=0.5):
    num_dts = dt_bboxes.shape[0]
    vaild_dts = np.array([False] * num_dts)
    num_press = 0

    for idx in range(num_dts):
        if vaild_dts[idx]:
            continue
        top_bbox = dt_bboxes[idx]
        for iidx in range(idx + 1, num_dts):
            if vaild_dts[iidx]:
                continue
            sub_bbox = dt_bboxes[iidx]
            iou = iou_overlap(top_bbox, sub_bbox)
            if iou >= iou_thresh:
                num_press += 1
                vaild_dts[iidx] = True
    return dt_bboxes[~vaild_dts]


def diff(res_cpp, res_py):
    if isinstance(res_cpp, list):
        res_cpp = np.array(res_cpp)
    if isinstance(res_py, list):
        res_py = np.array(res_py)
    print(np.sum(np.abs(res_cpp - res_py)))


if __name__ == "__main__":
    dt_bboxes = np.abs(np.random.rand(1000, 4) * 1000).astype(dtype=np.int32)
    dt_bboxes = dt_bboxes.astype(dtype=np.float64)
    dt_bboxes[:, 2] += dt_bboxes[:, 0]
    dt_bboxes[:, 3] += dt_bboxes[:, 1]
    iou_thresh = 0.5

    dt_tmp = copy.deepcopy(dt_bboxes)
    t_cpp = time.time()
    res_cpp = nms_cpp(dt_tmp)
    print(f"cpp nms time {time.time() - t_cpp}")
    res_cpp = np.array(res_cpp)

    dt_tmp = copy.deepcopy(dt_bboxes)
    t_py = time.time()
    res_py = nms(dt_tmp, iou_thresh)
    print(f"python nms time {time.time() - t_py}")
    
    diff(res_cpp, res_py)