#include "fiff/formatting.hpp"

#include "fiff/datatypes.hpp"

const std::map<int,std::string>& Fiff::Formatting::tagKinds()
{
  return _tagKind;
}

const std::map<int,std::string>& Fiff::Formatting::tagTypes()
{
  return _tagType;
}

const std::map<int, std::string> &Fiff::Formatting::blockIds()
{
  return _blockID;
}

std::string Fiff::Formatting::asString(const Fiff::Tag& tag){
  std::stringstream stream;

  stream << formatTagMetaData(tag) << ", " << formatTagData(tag);

  return stream.str();
}

std::string Fiff::Formatting::getMapValue(const std::map<int,std::string>& map,
                                          int id)
{
  std::stringstream stream;

  auto mapEntry = map.find(id);
  if (mapEntry != map.end()) {
    stream << mapEntry->second;
  } else {
    stream << id;
  }

  return stream.str();
}

std::string Fiff::Formatting::formatTagMetaData(const Fiff::Tag &tag)
{
  std::stringstream stream;

  stream << "(" << tag.kind << ")" << getMapValue(_tagKind, tag.kind);
  stream << ", ";
  stream << "(" << tag.type << ")" << getMapValue(_tagType, tag.type);
  stream << ", ";
  stream << tag.size << " bytes";
  stream <<  ", next: " << tag.next;

  return stream.str();
}

std::string Fiff::Formatting::formatTagData(const Fiff::Tag& tag)
{
  if(tag.data == nullptr){
    return {};
  }
  std::stringstream stream;

  switch (tag.type){
    case 3:
    {
      stream << "data: ";
      if(tag.kind == 104 || tag.kind == 105)
      {
        stream << "(" << *static_cast<int *>(tag.data) << ")" << getMapValue(_blockID, *static_cast<int *>(tag.data));
      } else
      {
        stream << std::to_string(*static_cast<int *>(tag.data));
      }
      break;
    }
    case 30:
    {
      stream << "data: ";
      auto info = static_cast<Type::ch_info_rec *>(tag.data);
      stream << "scanNo " << info->scanNo << ", ";
      stream << "logNo " << info->logNo << ", ";
      stream << "kind " << info->kind << ", ";
      stream.precision(9);
      stream << "range " << info->range << ", ";
      stream << "cal " << info->cal;
    }
  }
  return stream.str();
}

const std::map<int,std::string> Fiff::Formatting::_tagKind
        {{1, "new_file"},
         {2, "close_file"},
         {3, "discard_file"},
         {4, "error_message"},
         {5, "suspend_reading"},
         {6, "fatal_error_message"},
         {7, "connection_check"},
         {8, "suspend_filing"},
         {9, "resume_filing"},
         {10, "raw_prebase"},
         {11, "raw_pick_list"},
         {12, "echo"},
         {13, "resume_reading"},
         {14, "dacq_system_type"},
         {15, "select_raw_ch"},
         {16, "playback_mode"},
         {17, "continue_file"},
         {18, "jitter_max"},
         {19, "stream_segment"},
         {100, "file_id"},
         {101, "dir_pointer"},
         {102, "dir"},
         {103, "block_id"},
         {104, "block_start"},
         {105, "block_end"},
         {106, "free_list"},
         {107, "free_block"},
         {108, "nop"},
         {109, "parent_file_id"},
         {110, "parent_block_id"},
         {111, "block_name"},
         {112, "block_version"},
         {113, "creator"},
         {114, "modifier"},
         {115, "ref_role"},
         {116, "ref_file_id"},
         {117, "ref_file_num"},
         {118, "ref_file_name"},
         {120, "ref_block_id"},
         {150, "dacq_pars"},
         {151, "dacq_stim"},
         {152, "device_type"},
         {153, "device_model"},
         {154, "device_serial"},
         {155, "device_site"},
         {156, "he_level_raw"},
         {157, "helium_level"},
         {158, "orig_file_guid"},
         {159, "utc_offset"},
         {200, "nchan"},
         {201, "sfreq"},
         {202, "data_pack"},
         {203, "ch_info"},
         {204, "meas_date"},
         {205, "subject"},
         {206, "description"},
         {207, "nave"},
         {208, "first_sample"},
         {209, "last_sample"},
         {210, "aspect_kind"},
         {211, "ref_event"},
         {212, "experimenter"},
         {213, "dig_point"},
         {214, "ch_pos_vec"},
         {215, "hpi_slopes"},
         {216, "hpi_ncoil"},
         {217, "req_event"},
         {218, "req_limit"},
         {219, "lowpass"},
         {220, "bad_chs"},
         {221, "artef_removal"},
         {222, "coord_trans"},
         {223, "highpass"},
         {224, "ch_cals_vec"},
         {225, "hpi_bad_chs"},
         {226, "hpi_corr_coeff"},
         {227, "event_comment"},
         {228, "no_samples"},
         {229, "first_time"},
         {230, "subave_size"},
         {231, "subave_first"},
         {233, "name"},
         {234, "dig_string"},
         {235, "line_freq"},
         {236, "hpi_coil_freq"},
         {237, "signal_channel"},
         {240, "hpi_coil_moments"},
         {241, "hpi_fit_goodness"},
         {242, "hpi_fit_accept"},
         {243, "hpi_fit_good_limit"},
         {244, "hpi_fit_dist_limit"},
         {245, "hpi_coil_no"},
         {246, "hpi_coils_used"},
         {247, "hpi_digitization_order"},
         {250, "ch_scan_no"},
         {251, "ch_logical_no"},
         {252, "ch_kind"},
         {253, "ch_range"},
         {254, "ch_cal"},
         {255, "ch_pos"},
         {256, "ch_unit"},
         {257, "ch_unit_mul"},
         {258, "ch_dacq_name"},
         {263, "sss_frame"},
         {264, "sss_job"},
         {265, "sss_origin"},
         {266, "sss_ord_in"},
         {267, "sss_ord_out"},
         {268, "sss_nmag"},
         {269, "sss_components"},
         {270, "sss_cal_chans"},
         {271, "sss_cal_corrs"},
         {272, "sss_st_corr"},
         {273, "sss_base_in"},
         {274, "sss_base_out"},
         {275, "sss_base_virt"},
         {276, "sss_norm"},
         {277, "sss_iterate"},
         {278, "sss_nfree"},
         {279, "sss_st_length"},
         {280, "gantry_type"},
         {281, "gantry_model"},
         {282, "gantry_angle"},
         {290, "sss_operator"},
         {291, "sss_psinv"},
         {292, "sss_ctc"},
         {300, "data_buffer"},
         {301, "data_skip"},
         {302, "epoch"},
         {303, "data_skip_samp"},
         {304, "data_buffer2"},
         {305, "time_stamp"},
         {350, "ch_coil_type"},
         {351, "ch_coord_frame"},
         {400, "subj_id"},
         {401, "subj_first_name"},
         {402, "subj_middle_name"},
         {403, "subj_last_name"},
         {404, "subj_birth_day"},
         {405, "subj_sex"},
         {406, "subj_hand"},
         {407, "subj_weight"},
         {408, "subj_height"},
         {409, "subj_comment"},
         {410, "subj_his_id"},
         {500, "proj_id"},
         {501, "proj_name"},
         {502, "proj_aim"},
         {503, "proj_persons"},
         {504, "proj_comment"},
         {600, "event_channels"},
         {601, "event_list"},
         {602, "event_channel"},
         {603, "event_bits"},
         {701, "squid_bias"},
         {702, "squid_offset"},
         {703, "squid_gate"},
         {800, "decoupler_matrix"},
         {801, "ctm_open_amps"},
         {802, "ctm_open_phase"},
         {803, "ctm_clos_amps"},
         {804, "ctm_clos_phase"},
         {805, "ctm_clos_dote"},
         {806, "ctm_open_dote"},
         {807, "ctm_exci_freq"},
         {1101, "ref_path"},
         {2001, "volume_type"},
         {2002, "mri_source_format"},
         {2003, "mri_pixel_encoding"},
         {2004, "mri_pixel_data_offset"},
         {2005, "mri_pixel_scale"},
         {2006, "mri_pixel_data"},
         {2007, "mri_pixel_overlay_encoding"},
         {2008, "mri_pixel_overlay_data"},
         {2009, "mri_bounding_box"},
         {2010, "mri_width"},
         {2011, "mri_width_m"},
         {2012, "mri_height"},
         {2013, "mri_height_m"},
         {2014, "mri_depth"},
         {2015, "mri_depth_m"},
         {2016, "mri_thickness"},
         {2017, "mri_scene_aim"},
         {2018, "mri_calibration_scale"},
         {2019, "mri_calibration_offset"},
         {2020, "mri_orig_source_path"},
         {2021, "mri_orig_source_format"},
         {2022, "mri_orig_pixel_encoding"},
         {2023, "mri_orig_pixel_data_offset"},
         {2024, "mri_time"},
         {2030, "mri_voxel_data"},
         {2031, "mri_voxel_encoding"},
         {2032, "voxel_nchannels"},
         {2040, "mri_diffusion_weight"},
         {2041, "mri_diffusion_param"},
         {2100, "mri_mrilab_setup"},
         {2200, "mri_seg_region_id"},
         {3000, "conductor_model_kind"},
         {3001, "sphere_origin"},
         {3002, "sphere_coord_frame"},
         {3003, "sphere_layers"},
         {3101, "bem_surf_id"},
         {3102, "bem_surf_name"},
         {3103, "bem_surf_nnode"},
         {3104, "bem_surf_ntri"},
         {3105, "bem_surf_nodes"},
         {3106, "bem_surf_triangles"},
         {3107, "bem_surf_normals"},
         {3108, "bem_surf_curvs"},
         {3109, "bem_surf_curv_values"},
         {3110, "bem_pot_solution"},
         {3111, "bem_approx"},
         {3112, "bem_coord_frame"},
         {3113, "bem_sigma"},
         {3201, "source_dipole"},
         {3300, "beamformer_instructions"},
         {3401, "xfit_lead_products"},
         {3402, "xfit_map_products"},
         {3403, "xfit_grad_map_products"},
         {3404, "xfit_vol_integration"},
         {3405, "xfit_integration_radius"},
         {3406, "xfit_conductor_model_name"},
         {3407, "xfit_conductor_model_trans_name"},
         {3408, "xfit_cont_surf_type"},
         {3411, "proj_item_kind"},
         {3412, "proj_item_time"},
         {3413, "proj_item_ign_chs"},
         {3414, "proj_item_nvec"},
         {3415, "proj_item_vectors"},
         {3416, "proj_item_definition"},
         {3417, "proj_item_ch_name_list"},
         {4001, "vol_id"},
         {4002, "vol_name"},
         {4003, "vol_owner_id"},
         {4004, "vol_owner_name"},
         {4005, "vol_owner_real_name"},
         {4006, "vol_type"},
         {4007, "vol_host"},
         {4008, "vol_real_root"},
         {4009, "vol_symbolic_root"},
         {4010, "vol_mount_point"},
         {4011, "vol_blocks"},
         {4012, "vol_free_blocks"},
         {4013, "vol_avail_blocks"},
         {4014, "vol_block_size"},
         {4015, "vol_directory"},
         {10300, "mem_data_buffer"},
         {3500, "#<reserved>"},
         {3501, "xplotter_layout"},
         {3502, "mne_row_names"},
         {3503, "mne_col_names"},
         {3504, "mne_nrow"},
         {3505, "mne_ncol"},
         {3506, "mne_coord_frame"},
         {3507, "mne_ch_name_list"},
         {3508, "mne_file_name"},
         {3510, "mne_source_space_points"},
         {3511, "mne_source_space_normals"},
         {3512, "mne_source_space_npoints"},
         {3513, "mne_source_space_selection"},
         {3514, "mne_source_space_nuse"},
         {3515, "mne_source_space_nearest"},
         {3516, "mne_source_space_nearest_dist"},
         {3517, "mne_source_space_id"},
         {3518, "mne_source_space_type"},
         {3519, "mne_source_space_vertices"},
         {3520, "mne_forward_solution"},
         {3521, "mne_source_orientation"},
         {3522, "mne_included_methods"},
         {3523, "mne_forward_solution_grad"},
         {3530, "mne_cov_kind"},
         {3531, "mne_cov_dim"},
         {3532, "mne_cov"},
         {3533, "mne_cov_diag"},
         {3534, "mne_cov_eigenvalues"},
         {3535, "mne_cov_eigenvectors"},
         {3536, "mne_cov_nfree"},
         {3537, "mne_cov_method"},
         {3538, "mne_cov_score"},
         {3540, "mne_inverse_leads"},
         {3541, "mne_inverse_fields"},
         {3542, "mne_inverse_sing"},
         {3543, "mne_priors_used"},
         {3544, "mne_inverse_full"},
         {3545, "mne_inverse_source_orientations"},
         {3546, "mne_inverse_leads_weighted"},
         {3547, "mne_inverse_source_unit"},
         {3550, "mne_env_working_dir"},
         {3551, "mne_env_command_line"},
         {3552, "mne_external_big_endian"},
         {3553, "mne_external_little_endian"},
         {3560, "mne_proj_item_active"},
         {3561, "mne_event_list"},
         {3562, "mne_hemi"},
         {3563, "mne_data_skip_nop"},
         {3564, "mne_orig_ch_info"},
         {3565, "mne_event_trigger_mask"},
         {3566, "mne_event_comments"},
         {3567, "mne_custom_ref"},
         {3568, "mne_baseline_min"},
         {3569, "mne_baseline_max"},
         {3570, "mne_morph_map"},
         {3571, "mne_morph_map_from"},
         {3572, "mne_morph_map_to"},
         {3580, "mne_ctf_comp_kind"},
         {3581, "mne_ctf_comp_data"},
         {3582, "mne_ctf_comp_calibrated"},
         {3585, "mne_derivation_data"},
         {3597, "mne_source_space_interpolator"},
         {3598, "mne_source_space_mri_file"},
         {3590, "mne_source_space_ntri"},
         {3591, "mne_source_space_triangles"},
         {3592, "mne_source_space_nuse_tri"},
         {3593, "mne_source_space_use_triangles"},
         {3594, "mne_source_space_nneighbors"},
         {3595, "mne_source_space_neighbors"},
         {3596, "mne_source_space_voxel_dims"},
         {3599, "mne_source_space_dist"},
         {3600, "mne_source_space_dist_limit"},
         {3601, "mne_ica_interface_params"},
         {3602, "mne_ica_channel_names"},
         {3603, "mne_ica_whitener"},
         {3604, "mne_ica_pca_components"},
         {3605, "mne_ica_pca_explained_var"},
         {3606, "mne_ica_pca_mean"},
         {3607, "mne_ica_matrix"},
         {3608, "mne_ica_bads"},
         {3609, "mne_ica_misc_params"},
         {3610, "mne_surface_map_data"},
         {3611, "mne_surface_map_kind"},
         {3612, "mne_kit_system_id"},
         {3700, "mne_rt_command"},
         {3701, "mne_rt_client_id"},
         {3800, "mne_epochs_selection"},
         {3801, "mne_epochs_drop_log"},
         {3802, "mne_epochs_reject"},
         {3803, "mne_epochs_raw_sfreq"}};

const std::map<int, std::string> Fiff::Formatting::_tagType
        {{0, "void"},
         {1, "byte"},
         {2, "short"},
         {3, "int32"},
         {4, "float"},
         {5, "double"},
         {6, "julian"},
         {7, "ushort"},
         {8, "uint32"},
         {9, "uint64"},
         {10, "string"},
         {11, "int64"},
         {13, "dau_pack13"},
         {14, "dau_pack14"},
         {16, "dau_pack16"},
         {20, "complex_float"},
         {21, "complex_double"},
         {23, "old_pack"},
         {30, "ch_info_struct"},
         {31, "id_struct"},
         {32, "dir_entry_struct"},
         {33, "dig_point_struct"},
         {34, "ch_pos_struct"},
         {35, "coord_trans_struct"},
         {36, "dig_string_struct"},
         {37, "stream_segment_struct"}};


const std::map<int, std::string> Fiff::Formatting::_blockID
        {{999, "root"},
         {100, "meas"},
         {101, "meas_info"},
         {102, "raw_data"},
         {103, "processed_data"},
         {104, "evoked"},
         {105, "aspect"},
         {106, "subject"},
         {107, "isotrak"},
         {108, "hpi_meas"},
         {109, "hpi_result"},
         {110, "hpi_coil"},
         {111, "project"},
         {112, "continuous_data"},
         {113, "ch_info"},
         {114, "void"},
         {115, "events"},
         {116, "index"},
         {117, "dacq_pars"},
         {118, "ref"},
         {119, "ias_raw_data"},
         {120, "ias_aspect"},
         {121, "hpi_subsystem"},
         {122, "phantom_subsystem"},
         {123, "status_subsystem"},
         {124, "device_info"},
         {125, "helium_info"},
         {126, "channel_info"}};

