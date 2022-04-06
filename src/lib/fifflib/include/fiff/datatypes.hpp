#ifndef FIFFFILEEXPLORER_DATATYPES_HPP
#define FIFFFILEEXPLORER_DATATYPES_HPP

#include <cstdint>
#include <climits>

namespace Fiff {

static_assert(CHAR_BIT == 8, "Only 8-bit byte systems supported.");

enum class Kind : int32_t {
  new_file = 1,
  close_file = 2,
  discard_file = 3,
  error_message = 4,
  suspend_reading = 5,
  fatal_error_message = 6,
  connection_check = 7,
  suspend_filing = 8,
  resume_filing = 9,
  raw_prebase = 10,
  raw_pick_list = 11,
  echo = 12,
  resume_reading = 13,
  dacq_system_type = 14,
  select_raw_ch = 15,
  playback_mode = 16,
  continue_file = 17,
  jitter_max = 18,
  stream_segment = 19,
  file_id = 100,
  dir_pointer = 101,
  dir = 102,
  block_id = 103,
  block_start = 104,
  block_end = 105,
  free_list = 106,
  free_block = 107,
  nop = 108,
  parent_file_id = 109,
  parent_block_id = 110,
  block_name = 111,
  block_version = 112,
  creator = 113,
  modifier = 114,
  ref_role = 115,
  ref_file_id = 116,
  ref_file_num = 117,
  ref_file_name = 118,
  ref_block_id = 120,
  dacq_pars = 150,
  dacq_stim = 151,
  device_type = 152,
  device_model = 153,
  device_serial = 154,
  device_site = 155,
  he_level_raw = 156,
  helium_level = 157,
  orig_file_guid = 158,
  utc_offset = 159,
  nchan = 200,
  sfreq = 201,
  data_pack = 202,
  ch_info = 203,
  meas_date = 204,
  subject = 205,
  description = 206,
  nave = 207,
  first_sample = 208,
  last_sample = 209,
  aspect_kind = 210,
  ref_event = 211,
  experimenter = 212,
  dig_point = 213,
  ch_pos_vec = 214,
  hpi_slopes = 215,
  hpi_ncoil = 216,
  req_event = 217,
  req_limit = 218,
  lowpass = 219,
  bad_chs = 220,
  artef_removal = 221,
  coord_trans = 222,
  highpass = 223,
  ch_cals_vec = 224,
  hpi_bad_chs = 225,
  hpi_corr_coeff = 226,
  event_comment = 227,
  no_samples = 228,
  first_time = 229,
  subave_size = 230,
  subave_first = 231,
  name = 233,
  dig_string = 234,
  line_freq = 235,
  hpi_coil_freq = 236,
  signal_channel = 237,
  hpi_coil_moments = 240,
  hpi_fit_goodness = 241,
  hpi_fit_accept = 242,
  hpi_fit_good_limit = 243,
  hpi_fit_dist_limit = 244,
  hpi_coil_no = 245,
  hpi_coils_used = 246,
  hpi_digitization_order = 247,
  ch_scan_no = 250,
  ch_logical_no = 251,
  ch_kind = 252,
  ch_range = 253,
  ch_cal = 254,
  ch_pos = 255,
  ch_unit = 256,
  ch_unit_mul = 257,
  ch_dacq_name = 258,
  sss_frame = 263,
  sss_job = 264,
  sss_origin = 265,
  sss_ord_in = 266,
  sss_ord_out = 267,
  sss_nmag = 268,
  sss_components = 269,
  sss_cal_chans = 270,
  sss_cal_corrs = 271,
  sss_st_corr = 272,
  sss_base_in = 273,
  sss_base_out = 274,
  sss_base_virt = 275,
  sss_norm = 276,
  sss_iterate = 277,
  sss_nfree = 278,
  sss_st_length = 279,
  gantry_type = 280,
  gantry_model = 281,
  gantry_angle = 282,
  sss_operator = 290,
  sss_psinv = 291,
  sss_ctc = 292,
  data_buffer = 300,
  data_skip = 301,
  epoch = 302,
  data_skip_samp = 303,
  data_buffer2 = 304,
  time_stamp = 305,
  ch_coil_type = 350,
  ch_coord_frame = 351,
  subj_id = 400,
  subj_first_name = 401,
  subj_middle_name = 402,
  subj_last_name = 403,
  subj_birth_day = 404,
  subj_sex = 405,
  subj_hand = 406,
  subj_weight = 407,
  subj_height = 408,
  subj_comment = 409,
  subj_his_id = 410,
  proj_id = 500,
  proj_name = 501,
  proj_aim = 502,
  proj_persons = 503,
  proj_comment = 504,
  event_channels = 600,
  event_list = 601,
  event_channel = 602,
  event_bits = 603,
  squid_bias = 701,
  squid_offset = 702,
  squid_gate = 703,
  decoupler_matrix = 800,
  ctm_open_amps = 801,
  ctm_open_phase = 802,
  ctm_clos_amps = 803,
  ctm_clos_phase = 804,
  ctm_clos_dote = 805,
  ctm_open_dote = 806,
  ctm_exci_freq = 807,
  ref_path = 1101,
  volume_type = 2001,
  mri_source_format = 2002,
  mri_pixel_encoding = 2003,
  mri_pixel_data_offset = 2004,
  mri_pixel_scale = 2005,
  mri_pixel_data = 2006,
  mri_pixel_overlay_encoding = 2007,
  mri_pixel_overlay_data = 2008,
  mri_bounding_box = 2009,
  mri_width = 2010,
  mri_width_m = 2011,
  mri_height = 2012,
  mri_height_m = 2013,
  mri_depth = 2014,
  mri_depth_m = 2015,
  mri_thickness = 2016,
  mri_scene_aim = 2017,
  mri_calibration_scale = 2018,
  mri_calibration_offset = 2019,
  mri_orig_source_path = 2020,
  mri_orig_source_format = 2021,
  mri_orig_pixel_encoding = 2022,
  mri_orig_pixel_data_offset = 2023,
  mri_time = 2024,
  mri_voxel_data = 2030,
  mri_voxel_encoding = 2031,
  voxel_nchannels = 2032,
  mri_diffusion_weight = 2040,
  mri_diffusion_param = 2041,
  mri_mrilab_setup = 2100,
  mri_seg_region_id = 2200,
  conductor_model_kind = 3000,
  sphere_origin = 3001,
  sphere_coord_frame = 3002,
  sphere_layers = 3003,
  bem_surf_id = 3101,
  bem_surf_name = 3102,
  bem_surf_nnode = 3103,
  bem_surf_ntri = 3104,
  bem_surf_nodes = 3105,
  bem_surf_triangles = 3106,
  bem_surf_normals = 3107,
  bem_surf_curvs = 3108,
  bem_surf_curv_values = 3109,
  bem_pot_solution = 3110,
  bem_approx = 3111,
  bem_coord_frame = 3112,
  bem_sigma = 3113,
  source_dipole = 3201,
  beamformer_instructions = 3300,
  xfit_lead_products = 3401,
  xfit_map_products = 3402,
  xfit_grad_map_products = 3403,
  xfit_vol_integration = 3404,
  xfit_integration_radius = 3405,
  xfit_conductor_model_name = 3406,
  xfit_conductor_model_trans_name = 3407,
  xfit_cont_surf_type = 3408,
  proj_item_kind = 3411,
  proj_item_time = 3412,
  proj_item_ign_chs = 3413,
  proj_item_nvec = 3414,
  proj_item_vectors = 3415,
  proj_item_definition = 3416,
  proj_item_ch_name_list = 3417,
  vol_id = 4001,
  vol_name = 4002,
  vol_owner_id = 4003,
  vol_owner_name = 4004,
  vol_owner_real_name = 4005,
  vol_type = 4006,
  vol_host = 4007,
  vol_real_root = 4008,
  vol_symbolic_root = 4009,
  vol_mount_point = 4010,
  vol_blocks = 4011,
  vol_free_blocks = 4012,
  vol_avail_blocks = 4013,
  vol_block_size = 4014,
  vol_directory = 4015,
  reserved = 3500,
  xplotter_layout = 3501,
  mne_row_names = 3502,
  mne_col_names = 3503,
  mne_nrow = 3504,
  mne_ncol = 3505,
  mne_coord_frame = 3506,
  mne_ch_name_list = 3507,
  mne_file_name = 3508,
  mne_source_space_points = 3510,
  mne_source_space_normals = 3511,
  mne_source_space_npoints = 3512,
  mne_source_space_selection = 3513,
  mne_source_space_nuse = 3514,
  mne_source_space_nearest = 3515,
  mne_source_space_nearest_dist = 3516,
  mne_source_space_id = 3517,
  mne_source_space_type = 3518,
  mne_source_space_vertices = 3519,
  mne_forward_solution = 3520,
  mne_source_orientation = 3521,
  mne_included_methods = 3522,
  mne_forward_solution_grad = 3523,
  mne_cov_kind = 3530,
  mne_cov_dim = 3531,
  mne_cov = 3532,
  mne_cov_diag = 3533,
  mne_cov_eigenvalues = 3534,
  mne_cov_eigenvectors = 3535,
  mne_cov_nfree = 3536,
  mne_cov_method = 3537,
  mne_cov_score = 3538,
  mne_inverse_leads = 3540,
  mne_inverse_fields = 3541,
  mne_inverse_sing = 3542,
  mne_priors_used = 3543,
  mne_inverse_full = 3544,
  mne_inverse_source_orientations = 3545,
  mne_inverse_leads_weighted = 3546,
  mne_inverse_source_unit = 3547,
  mne_env_working_dir = 3550,
  mne_env_command_line = 3551,
  mne_external_big_endian = 3552,
  mne_external_little_endian = 3553,
  mne_proj_item_active = 3560,
  mne_event_list = 3561,
  mne_hemi = 3562,
  mne_data_skip_nop = 3563,
  mne_orig_ch_info = 3564,
  mne_event_trigger_mask = 3565,
  mne_event_comments = 3566,
  mne_custom_ref = 3567,
  mne_baseline_min = 3568,
  mne_baseline_max = 3569,
  mne_morph_map = 3570,
  mne_morph_map_from = 3571,
  mne_morph_map_to = 3572,
  mne_ctf_comp_kind = 3580,
  mne_ctf_comp_data = 3581,
  mne_ctf_comp_calibrated = 3582,
  mne_derivation_data = 3585,
  mne_source_space_interpolator = 3597,
  mne_source_space_mri_file = 3598,
  mne_source_space_ntri = 3590,
  mne_source_space_triangles = 3591,
  mne_source_space_nuse_tri = 3592,
  mne_source_space_use_triangles = 3593,
  mne_source_space_nneighbors = 3594,
  mne_source_space_neighbors = 3595,
  mne_source_space_voxel_dims = 3596,
  mne_source_space_dist = 3599,
  mne_source_space_dist_limit = 3600,
  mne_ica_interface_params = 3601,
  mne_ica_channel_names = 3602,
  mne_ica_whitener = 3603,
  mne_ica_pca_components = 3604,
  mne_ica_pca_explained_var = 3605,
  mne_ica_pca_mean = 3606,
  mne_ica_matrix = 3607,
  mne_ica_bads = 3608,
  mne_ica_misc_params = 3609,
  mne_surface_map_data = 3610,
  mne_surface_map_kind = 3611,
  mne_kit_system_id = 3612,
  mne_rt_command = 3700,
  mne_rt_client_id = 3701,
  mne_epochs_selection = 3800,
  mne_epochs_drop_log = 3801,
  mne_epochs_reject = 3802,
  mne_epochs_raw_sfreq = 3803,
  mem_data_buffer = 10300
};

enum class Type : int32_t {
  void_ = 0,
  byte_ = 1,
  short_ = 2,
  int32_ = 3,
  float_ = 4,
  double_ = 5,
  julian_ = 6,
  ushort_ = 7,
  uint32_ = 8,
  uint64_ = 9,
  string_ = 10,
  int64_ = 11,
  dau_pack13_ = 13,
  dau_pack14_ = 14,
  dau_pack16_ = 16,
  complex_float_ = 20,
  complex_double_ = 21,
  old_pack_ = 23,
  ch_info_struct_ = 30,
  id_struct_ = 31,
  dir_entry_struct_ = 32,
  dig_point_struct_ = 33,
  ch_pos_struct_ = 34,
  coord_trans_struct_ = 35,
  dig_string_struct_ = 36,
  stream_segment_struct_ = 37
};

enum class Block : int32_t {
  root = 999,
  meas = 100,
  meas_info = 101,
  raw_data = 102,
  processed_data = 103,
  evoked = 104,
  aspect = 105,
  subject = 106,
  isotrak = 107,
  hpi_meas = 108,
  hpi_result = 109,
  hpi_coil = 110,
  project = 111,
  continuous_data = 112,
  ch_info = 113,
  void_block = 114,
  events = 115,
  index = 116,
  dacq_pars = 117,
  ref = 118,
  ias_raw_data = 119,
  ias_aspect = 120,
  hpi_subsystem = 121,
  phantom_subsystem = 122,
  status_subsystem = 123,
  device_info = 124,
  helium_info = 125,
  channel_inf = 126
};

namespace Data {
struct ch_info_t {
  int32_t scanNo;       /**< Position of this channel in scanning order. */
  int32_t logNo;        /**< Logical channel number. These must be unique within channels of the same kind. */
  int32_t kind;         /**< Kind of the channel described (MEG, EEG, EOG, etc.) */
  float range;          /**< The raw data values must be multiplied by this to get into volts at the electronics output. */
  float cal;            /**< Calibration of the channel. If the raw data values are multiplied by range*cal, the result is in units given by unit and unit_mul. */
  int32_t coil_type;    /**< Kind of MEG coil or kind of EEG channel. */
  float r0[3];          /**< Coil coordinate system origin. For EEG electrodes, this is the location of the electrode. */
  float ex[3];          /**< Coil coordinate system unit vector ex. For EEG electrodes, this specifies the location of a reference electrode. Set to (0,0,0) for no reference. */
  float ey[3];          /**< Coil coordinate system unit vector ey. This is ignored for EEG electrodes. */
  float ez[3];          /**< Coil coordinate system unit vector ez . This is ignored for EEG electrodes. */
  int32_t unit;         /**< The real-world unit-of measure. */
  int32_t unit_mul;     /**< The unit multiplier. The result given by range*cal*data is in units unit*10^unit_mul. */
}; //mSize is 80 bytes

struct ch_pos_t {
  int32_t coil_type;
  float r0[3];
  float ex[3];
  float ey[3];
  float ez[3];
}; //mSize is 48 bytes

struct ch_info_rec {
  int32_t scanNo;       /**< Position of this channel in scanning order. */
  int32_t logNo;        /**< Logical channel number. These must be unique within channels of the same kind. */
  int32_t kind;         /**< Kind of the channel described (MEG, EEG, EOG, etc.) */
  float range;          /**< The raw data values must be multiplied by this to get into volts at the electronics output. */
  float cal;            /**< Calibration of the channel. If the raw data values are multiplied by range*cal, the result is in units given by unit and unit_mul. */
  ch_pos_t chpos;       /**< Channel position. */
  int32_t unit;         /**< The real-world unit-of measure. */
  int32_t unit_mul;     /**< The unit multiplier. The result given by range*cal*data is in units unit*10^unit_mul. */
  char ch_name[16];     /**< Descriptive name for the channel. */
}; //mSize is 96 bytes

struct id_t {
  int32_t version;
  int32_t machid[2];
  int32_t time_sec;
  int32_t time_usec;
};//total mSize is 20 bytes

}//namespace Type
}//namespace Fiff
#endif //FIFFFILEEXPLORER_DATATYPES_HPP
