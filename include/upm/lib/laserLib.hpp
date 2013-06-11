#ifndef LASERLIB_HPP
#define LASERLIB_HPP

//#include "sensor_msgs/LaserScan.h"
#include <filters/filter_chain.h>
#include "sensor_msgs/LaserScan.h"
#include "lengine.hpp"
#include <upm/ClusteredScan.h>

/**
 * A class used as a ROS wrapper for the lengine class.
 */
class laserLib {
private:

  /// Needed by getClusters()
  LSL_Point3D_str cogLSL;
  LSL_Point3D_str origin;
  geometry_msgs::Point32 pt;
  geometry_msgs::Point32 cogROS;

  /// The shadow filter to preprocess the laser
  filters::FilterChain<sensor_msgs::LaserScan> laserFilter;
  /// The filtered scan
  sensor_msgs::LaserScan filtScan;

  /// This is a people2d_engine class to hold the laser scan data for it.
  laserscan_data libScan;

  /// people2d_engine object used to make the segmentation and compute the features.
  lengine libEngine;
  /// Parameters of the libEngine. Initialized in constructor.
  sw_param_str libEngineParams;

  ///  Vector to hold the clusters of each scan in people2d_engine format
  std::vector<LSL_Point3D_container> clusters;  // lgeometry.hpp

  /// The feature vector
  std::vector < std::vector <float> > descriptor;
  float angle_min;
  float angle_max;
  float angle_inc;

  // Helping variables to copy the header to the new msgs
  ros::Time stamp;
  uint32_t seq;
  std::string frame_id;

  /**
   *
   * @param ls[in] The input scan to be converted
   */
  void scan2lib(sensor_msgs::LaserScan &ls);

  /**
   *
   * @param features[out] Exported cluster features.
   */
  void features2ROS(upm::ClusteredScan &features);

public:
  laserLib();
  ~laserLib();

  /**
   *
   * @param features[out] Exported cluster features
   */
  void getFeatures(upm::ClusteredScan &features);

  /**
   *
   * @param features[out] Where the clusters are going to be exported.
   */
  void getClusters(upm::ClusteredScan &laserClusters);

  /**
   *
   * @param ls LaserScan to be loaded
   */
  void loadScan(sensor_msgs::LaserScan ls);
};

#endif
