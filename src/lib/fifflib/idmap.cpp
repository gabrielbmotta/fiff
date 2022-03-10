//
// Created by Gabriel Motta on 3/7/22.
//

#include "fiff/idmap.hpp"
#include "fiff/datatypes.hpp"

const std::map<int,std::string>& Fiff::Formatting::tagKinds()
{
  return _tagKind;
}

const std::map<int,std::string>& Fiff::Formatting::tagTypes()
{
  return _tagType;
}

std::string Fiff::Formatting::fullTagAsString(const Fiff::Tag& tag){
  std::stringstream stream;

  stream << formatTagMetaData(tag) << ", " << formatTagData(tag);

  return stream.str();
}

std::string Fiff::Formatting::fullFileAsString(Fiff::File& file)
{
  std::stringstream stream;
  char padding = '\t';
  int indent = 0;

  while(file.isOpen() && !file.isAtEnd()){
    auto tag = file.readNextTag();
    if (tag.kind == 105){
      --indent;
    }
    for (int i = 0 ; i < indent ; ++i){
      stream << padding;
    }
    stream << fullTagAsString(tag);
    stream << "\n";
    if(tag.kind == 104){
      ++indent;
    }
  }

  return stream.str();
}

std::string Fiff::Formatting::toString(const Fiff::Tag &tag)
{
  std::stringstream stream;

  stream << formatTagMetaData(tag) << ", " << formatTagData(tag);

  return stream.str();
}

std::string Fiff::Formatting::toString(Fiff::File &file)
{
  std::stringstream stream;
  char padding = '\t';
  int indent = 0;

  while(file.isOpen() && !file.isAtEnd()){
    auto tag = file.readNextTag();

    if (tag.kind == 105){
      --indent;
    }
    for (int i = 0 ; i < indent ; ++i){
      stream << padding;
    }
    stream << toString(tag);
    stream << "\n";
    if(tag.kind == 104){
      ++indent;
    }
  }

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

  stream << getMapValue(_tagKind, tag.kind);
  stream << ", ";
  stream << getMapValue(_tagType, tag.type);
  stream << ", ";
  stream << tag.size << " bytes";
  stream <<  ", next: " << tag.next;

  return stream.str();
}

std::string Fiff::Formatting::formatTagData(const Fiff::Tag& tag)
{
  std::stringstream stream;

  switch (tag.type){
    case 3:
    {
      stream << "data: ";
      if(tag.kind == 104 || tag.kind == 105)
      {
        stream << getMapValue(_blockID, *static_cast<int *>(tag.data));
      } else
      {
        stream << std::to_string(*static_cast<int *>(tag.data));
      }
      break;
    }
    case 30:
    {
      stream << "data: ";
      auto info = static_cast<ch_info_rec *>(tag.data);
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

std::map<int,std::string> Fiff::Formatting::_tagKind
        {{1, "(1)new_file"},
         {2, "(2)close_file"},
         {3, "(3)discard_file"},
         {4, "(4)error_message"},
         {5, "(5)suspend_reading"},
         {6, "(6)fatal_error_message"},
         {7, "(7)connection_check"},
         {8, "(8)suspend_filing"},
         {9, "(9)resume_filing"},
         {10, "(10)raw_prebase"},
         {11, "(11)raw_pick_list"},
         {12, "(12)echo"},
         {13, "(13)resume_reading"},
         {14, "(14)dacq_system_type"},
         {15, "(15)select_raw_ch"},
         {16, "(16)playback_mode"},
         {17, "(17)continue_file"},
         {18, "(18)jitter_max"},
         {19, "(19)stream_segment"},
         {100, "(100)file_id"},
         {101, "(101)dir_pointer"},
         {102, "(102)dir"},
         {103, "(103)block_id"},
         {104, "(104)block_start"},
         {105, "(105)block_end"},
         {106, "(106)free_list"},
         {107, "(107)free_block"},
         {108, "(108)nop"},
         {109, "(109)parent_file_id"},
         {110, "(110)parent_block_id"},
         {111, "(111)block_name"},
         {112, "(112)block_version"},
         {113, "(113)creator"},
         {114, "(114)modifier"},
         {115, "(115)ref_role"},
         {116, "(116)ref_file_id"},
         {117, "(117)ref_file_num"},
         {118, "(118)ref_file_name"},
         {120, "(120)ref_block_id"},
         {150, "(150)dacq_pars"},
         {151, "(151)dacq_stim"},
         {152, "(152)device_type"},
         {153, "(153)device_model"},
         {154, "(154)device_serial"},
         {155, "(155)device_site"},
         {156, "(156)he_level_raw"},
         {157, "(157)helium_level"},
         {158, "(158)orig_file_guid"},
         {159, "(159)utc_offset"},
         {200, "(200)nchan"},
         {201, "(201)sfreq"},
         {202, "(202)data_pack"},
         {203, "(203)ch_info"},
         {204, "(204)meas_date"},
         {205, "(205)subject"},
         {206, "(206)description"},
         {207, "(207)nave"},
         {208, "(208)first_sample"},
         {209, "(209)last_sample"},
         {210, "(210)aspect_kind"},
         {211, "(211)ref_event"},
         {212, "(212)experimenter"},
         {213, "(213)dig_point"},
         {214, "(214)ch_pos_vec"},
         {215, "(215)hpi_slopes"},
         {216, "(216)hpi_ncoil"},
         {217, "(217)req_event"},
         {218, "(218)req_limit"},
         {219, "(219)lowpass"},
         {220, "(220)bad_chs"},
         {221, "(221)artef_removal"},
         {222, "(222)coord_trans"},
         {223, "(223)highpass"},
         {224, "(224)ch_cals_vec"},
         {225, "(225)hpi_bad_chs"},
         {226, "(226)hpi_corr_coeff"},
         {227, "(227)event_comment"},
         {228, "(228)no_samples"},
         {229, "(229)first_time"},
         {230, "(230)subave_size"},
         {231, "(231)subave_first"},
         {233, "(233)name"},
         {234, "(234)dig_string"},
         {235, "(235)line_freq"},
         {236, "(236)hpi_coil_freq"},
         {237, "(237)signal_channel"},
         {240, "(240)hpi_coil_moments"},
         {241, "(241)hpi_fit_goodness"},
         {242, "(242)hpi_fit_accept"},
         {243, "(243)hpi_fit_good_limit"},
         {244, "(244)hpi_fit_dist_limit"},
         {245, "(245)hpi_coil_no"},
         {246, "(246)hpi_coils_used"},
         {247, "(247)hpi_digitization_order"},
         {250, "(250)ch_scan_no"},
         {251, "(251)ch_logical_no"},
         {252, "(252)ch_kind"},
         {253, "(253)ch_range"},
         {254, "(254)ch_cal"},
         {255, "(255)ch_pos"},
         {256, "(256)ch_unit"},
         {257, "(257)ch_unit_mul"},
         {258, "(258)ch_dacq_name"},
         {263, "(263)sss_frame"},
         {264, "(264)sss_job"},
         {265, "(265)sss_origin"},
         {266, "(266)sss_ord_in"},
         {267, "(267)sss_ord_out"},
         {268, "(268)sss_nmag"},
         {269, "(269)sss_components"},
         {270, "(270)sss_cal_chans"},
         {271, "(271)sss_cal_corrs"},
         {272, "(272)sss_st_corr"},
         {273, "(273)sss_base_in"},
         {274, "(274)sss_base_out"},
         {275, "(275)sss_base_virt"},
         {276, "(276)sss_norm"},
         {277, "(277)sss_iterate"},
         {278, "(278)sss_nfree"},
         {279, "(279)sss_st_length"},
         {280, "(280)gantry_type"},
         {281, "(281)gantry_model"},
         {282, "(282)gantry_angle"},
         {290, "(290)sss_operator"},
         {291, "(291)sss_psinv"},
         {292, "(292)sss_ctc"},
         {300, "(300)data_buffer"},
         {301, "(301)data_skip"},
         {302, "(302)epoch"},
         {303, "(303)data_skip_samp"},
         {304, "(304)data_buffer2"},
         {305, "(305)time_stamp"},
         {350, "(350)ch_coil_type"},
         {351, "(351)ch_coord_frame"},
         {400, "(400)subj_id"},
         {401, "(401)subj_first_name"},
         {402, "(402)subj_middle_name"},
         {403, "(403)subj_last_name"},
         {404, "(404)subj_birth_day"},
         {405, "(405)subj_sex"},
         {406, "(406)subj_hand"},
         {407, "(407)subj_weight"},
         {408, "(408)subj_height"},
         {409, "(409)subj_comment"},
         {410, "(410)subj_his_id"},
         {500, "(500)proj_id"},
         {501, "(501)proj_name"},
         {502, "(502)proj_aim"},
         {503, "(503)proj_persons"},
         {504, "(504)proj_comment"},
         {600, "(600)event_channels"},
         {601, "(601)event_list"},
         {602, "(602)event_channel"},
         {603, "(603)event_bits"},
         {701, "(701)squid_bias"},
         {702, "(702)squid_offset"},
         {703, "(703)squid_gate"},
         {800, "(800)decoupler_matrix"},
         {801, "(801)ctm_open_amps"},
         {802, "(802)ctm_open_phase"},
         {803, "(803)ctm_clos_amps"},
         {804, "(804)ctm_clos_phase"},
         {805, "(805)ctm_clos_dote"},
         {806, "(806)ctm_open_dote"},
         {807, "(807)ctm_exci_freq"},
         {1101, "(1101)ref_path"},
         {2001, "(2001)volume_type"},
         {2002, "(2002)mri_source_format"},
         {2003, "(2003)mri_pixel_encoding"},
         {2004, "(2004)mri_pixel_data_offset"},
         {2005, "(2005)mri_pixel_scale"},
         {2006, "(2006)mri_pixel_data"},
         {2007, "(2007)mri_pixel_overlay_encoding"},
         {2008, "(2008)mri_pixel_overlay_data"},
         {2009, "(2009)mri_bounding_box"},
         {2010, "(2010)mri_width"},
         {2011, "(2011)mri_width_m"},
         {2012, "(2012)mri_height"},
         {2013, "(2013)mri_height_m"},
         {2014, "(2014)mri_depth"},
         {2015, "(2015)mri_depth_m"},
         {2016, "(2016)mri_thickness"},
         {2017, "(2017)mri_scene_aim"},
         {2018, "(2018)mri_calibration_scale"},
         {2019, "(2019)mri_calibration_offset"},
         {2020, "(2020)mri_orig_source_path"},
         {2021, "(2021)mri_orig_source_format"},
         {2022, "(2022)mri_orig_pixel_encoding"},
         {2023, "(2023)mri_orig_pixel_data_offset"},
         {2024, "(2024)mri_time"},
         {2030, "(2030)mri_voxel_data"},
         {2031, "(2031)mri_voxel_encoding"},
         {2032, "(2032)voxel_nchannels"},
         {2040, "(2040)mri_diffusion_weight"},
         {2041, "(2041)mri_diffusion_param"},
         {2100, "(2100)mri_mrilab_setup"},
         {2200, "(2200)mri_seg_region_id"},
         {3000, "(3000)conductor_model_kind"},
         {3001, "(3001)sphere_origin"},
         {3002, "(3002)sphere_coord_frame"},
         {3003, "(3003)sphere_layers"},
         {3101, "(3101)bem_surf_id"},
         {3102, "(3102)bem_surf_name"},
         {3103, "(3103)bem_surf_nnode"},
         {3104, "(3104)bem_surf_ntri"},
         {3105, "(3105)bem_surf_nodes"},
         {3106, "(3106)bem_surf_triangles"},
         {3107, "(3107)bem_surf_normals"},
         {3108, "(3108)bem_surf_curvs"},
         {3109, "(3109)bem_surf_curv_values"},
         {3110, "(3110)bem_pot_solution"},
         {3111, "(3111)bem_approx"},
         {3112, "(3112)bem_coord_frame"},
         {3113, "(3113)bem_sigma"},
         {3201, "(3201)source_dipole"},
         {3300, "(3300)beamformer_instructions"},
         {3401, "(3401)xfit_lead_products"},
         {3402, "(3402)xfit_map_products"},
         {3403, "(3403)xfit_grad_map_products"},
         {3404, "(3404)xfit_vol_integration"},
         {3405, "(3405)xfit_integration_radius"},
         {3406, "(3406)xfit_conductor_model_name"},
         {3407, "(3407)xfit_conductor_model_trans_name"},
         {3408, "(3408)xfit_cont_surf_type"},
         {3411, "(3411)proj_item_kind"},
         {3412, "(3412)proj_item_time"},
         {3413, "(3413)proj_item_ign_chs"},
         {3414, "(3414)proj_item_nvec"},
         {3415, "(3415)proj_item_vectors"},
         {3416, "(3416)proj_item_definition"},
         {3417, "(3417)proj_item_ch_name_list"},
         {3501, "(3501)xplotter_layout"},
         {4001, "(4001)vol_id"},
         {4002, "(4002)vol_name"},
         {4003, "(4003)vol_owner_id"},
         {4004, "(4004)vol_owner_name"},
         {4005, "(4005)vol_owner_real_name"},
         {4006, "(4006)vol_type"},
         {4007, "(4007)vol_host"},
         {4008, "(4008)vol_real_root"},
         {4009, "(4009)vol_symbolic_root"},
         {4010, "(4010)vol_mount_point"},
         {4011, "(4011)vol_blocks"},
         {4012, "(4012)vol_free_blocks"},
         {4013, "(4013)vol_avail_blocks"},
         {4014, "(4014)vol_block_size"},
         {4015, "(4015)vol_directory"},
         {10300, "(10300)mem_data_buffer"},};

std::map<int, std::string> Fiff::Formatting::_tagType
        {{0, "(0)void"},
         {1, "(1)byte"},
         {2, "(2)short"},
         {3, "(3)int"},
         {4, "(4)float"},
         {5, "(5)double"},
         {6, "(6)julian"},
         {7, "(7)ushort"},
         {8, "(8)uint"},
         {10, "(10)string"},
         {13, "(13)dau_pack13"},
         {14, "(14)dau_pack14"},
         {16, "(16)dau_pack16"},
         {23, "(23)old_pack"},
         {30, "(30)ch_info_struct"},
         {31, "(31)id_struct"},
         {32, "(32)dir_entry_struct"},
         {33, "(33)dig_point_struct"},
         {34, "(34)ch_pos_struct"},
         {35, "(35)coord_trans_struct"},
         {36, "(36)dig_string_struct"},
         {37, "(37)stream_segment_struct"},};


std::map<int, std::string> Fiff::Formatting::_blockID
        {{999, "(999)root"},
         {100, "(100)meas"},
         {101, "(101)meas_info"},
         {102, "(102)raw_data"},
         {103, "(103)processed_data"},
         {104, "(104)evoked"},
         {105, "(105)aspect"},
         {106, "(106)subject"},
         {107, "(107)isotrak"},
         {108, "(108)hpi_meas"},
         {109, "(109)hpi_result"},
         {110, "(110)hpi_coil"},
         {111, "(111)project"},
         {112, "(112)continuous_data"},
         {113, "(113)ch_info"},
         {114, "(114)void"},
         {115, "(115)events"},
         {116, "(116)index"},
         {117, "(117)dacq_pars"},
         {118, "(118)ref"},
         {119, "(119)ias_raw_data"},
         {120, "(120)ias_aspect"},
         {121, "(121)hpi_subsystem"},
         {122, "(122)phantom_subsystem"},
         {123, "(123)status_subsystem"},
         {124, "(124)device_info"},
         {125, "(125)helium_info"},
         {126, "(126)channel_info"}};
