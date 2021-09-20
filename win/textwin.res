Descartes  h4.Sun413
	XmMainWindow  mainwindow
		XmSeparatorGadget  Separator1
		XmSeparatorGadget  Separator2
		XmSeparatorGadget  Separator3
		XmRowColumn  menubar
			XmCascadeButtonGadget  file_cbtn
			XmCascadeButtonGadget  view_cbtn
			XmCascadeButtonGadget  options_cbtn
			XmCascadeButtonGadget  help_cbtn
			XmMenuShell  popup_file_pmnu
				XmRowColumn  file_pmnu
					XmCascadeButtonGadget  open_pbtn
					XmPushButtonGadget  run_pbtn
					XmPushButtonGadget  exit_pbtn
				XmRowColumn  options_pmnu
					XmCascadeButtonGadget  set_filenames_pbtn
					XmToggleButtonGadget  set_trace
					XmPushButtonGadget  default_x_resource_values_pbtn
				XmRowColumn  help_pmnu
					XmPushButtonGadget  overview_pbtn
					XmPushButtonGadget  product_information_pbtn
				XmRowColumn  view_pmnu
					XmToggleButtonGadget  animate_pbtn
					XmToggleButtonGadget  toolbar_pbtn
				XmMenuShell  popup_file_open_pulldown
					XmRowColumn  file_open_pulldown
						XmPushButtonGadget  load_descartes_spec
						XmPushButtonGadget  read_tree_file
						XmPushButtonGadget  read_log_file
						XmPushButtonGadget  read_input_file
						XmPushButtonGadget  read_output_file
					XmRowColumn  options_set_filenames_pmnu
						XmPushButtonGadget  log_file
						XmPushButtonGadget  input_file
						XmPushButtonGadget  output_file
		XmText  message_text
		XmPanedWindow  pane
			XmForm  toolbar_mgr
				XmPushButtonGadget  load_btn
				XmPushButtonGadget  run_btn
				XmPushButtonGadget  exit_btn
				XmLabelGadget  slowlbl
				XmScale  delay_scale
					XmLabelGadget  Title
					XmScrollBar  Scrollbar
				XmLabelGadget  fastlbl
			XmMainWindow  scrollwin
				XmDrawingArea  ScrolledWindowClipWindow
					XmDrawingArea  drawing_a
				XmScrollBar  VertScrollBar
				XmScrollBar  HorScrollBar
				XmSeparatorGadget  Separator1
				XmSeparatorGadget  Separator2
				XmSeparatorGadget  Separator3
			XmScrolledWindow  history_textSW
				XmScrollBar  HorScrollBar
				XmScrollBar  VertScrollBar
				XmText  history_text
			XmSash  sash
			XmSeparatorGadget  separator
			XmSash  sash
			XmSeparatorGadget  separator
			XmSash  sash
			XmSeparatorGadget  separator
	XmDialogShell  file_sel_popup
		XmFileSelectionBox  file_sel
			XmLabelGadget  Items
			XmScrolledWindow  ItemsListSW
				XmScrollBar  VertScrollBar
				XmScrollBar  HorScrollBar
				XmList  ItemsList
			XmLabelGadget  Selection
			XmTextField  Text
			XmSeparatorGadget  Separator
			XmPushButtonGadget  OK
			XmPushButtonGadget  Apply
			XmPushButtonGadget  Cancel
			XmPushButtonGadget  Help
			XmLabelGadget  FilterLabel
			XmLabelGadget  Dir
			XmTextField  FilterText
			XmScrolledWindow  DirListSW
				XmScrollBar  VertScrollBar
				XmScrollBar  HorScrollBar
				XmList  DirList
	XmDialogShell  err_dialog_popup
		XmMessageBox  err_dialog
			XmLabelGadget  Symbol
			XmLabelGadget  Message
			XmSeparatorGadget  Separator
			XmPushButtonGadget  OK
			XmPushButtonGadget  Cancel
			XmPushButtonGadget  Help
	XmDialogShell  rene_dialog_popup
		XmMessageBox  rene_dialog
			XmLabelGadget  Symbol
			XmLabelGadget  Message
			XmSeparatorGadget  Separator
			XmPushButtonGadget  OK
			XmPushButtonGadget  Cancel
			XmPushButtonGadget  Help
			XmRowColumn  manager
				XmFrame  draw_frame
					XmDrawingArea  draw_area
				XmLabelGadget  captiong
				XmRowColumn  headingg1_mgr
					XmLabelGadget  headingg1
				XmLabelGadget  headingg2
				XmForm  contrib_1
					XmLabelGadget  contrg
					XmLabelGadget  yearg
				XmForm  contrib_2
					XmLabelGadget  contrg
					XmLabelGadget  yearg
				XmForm  contrib_3
					XmLabelGadget  contrg
					XmLabelGadget  yearg
				XmForm  contrib_4
					XmLabelGadget  contrg
					XmLabelGadget  yearg
				XmForm  contrib_5
					XmLabelGadget  contrg
					XmLabelGadget  yearg
				XmForm  contrib_6
					XmLabelGadget  contrg
					XmLabelGadget  yearg
				XmForm  contrib_7
					XmLabelGadget  contrg
					XmLabelGadget  yearg
				XmForm  contrib_8
					XmLabelGadget  contrg
					XmLabelGadget  yearg
	XmDialogShell  rene_dialog_popup
		XmMessageBox  rene_dialog
			XmLabelGadget  Symbol
			XmLabelGadget  Message
			XmSeparatorGadget  Separator
			XmPushButtonGadget  OK
			XmPushButtonGadget  Cancel
			XmPushButtonGadget  Help
			XmRowColumn  manager
				XmFrame  draw_frame
					XmDrawingArea  draw_area
				XmLabelGadget  captiong
				XmRowColumn  headingg1_mgr
					XmLabelGadget  headingg1
				XmLabelGadget  headingg2
				XmForm  contrib_9
					XmLabelGadget  contrg
					XmLabelGadget  yearg
				XmForm  contrib_10
					XmLabelGadget  contrg
					XmLabelGadget  yearg
				XmForm  contrib_11
					XmLabelGadget  contrg
					XmLabelGadget  yearg
				XmForm  contrib_12
					XmLabelGadget  contrg
					XmLabelGadget  yearg
				XmForm  contrib_13
					XmLabelGadget  contrg
					XmLabelGadget  yearg
				XmForm  contrib_14
					XmLabelGadget  contrg
					XmLabelGadget  yearg
				XmForm  contrib_15
					XmLabelGadget  contrg
					XmLabelGadget  yearg
				XmForm  contrib_16
					XmLabelGadget  contrg
					XmLabelGadget  yearg
	TopLevelShell  display_text_shell
		XmMainWindow  mainwindow
			XmSeparatorGadget  Separator1
			XmSeparatorGadget  Separator2
			XmSeparatorGadget  Separator3
			XmRowColumn  menubar
				XmCascadeButtonGadget  file_cbtn
				XmMenuShell  popup_file_pmnu
					XmRowColumn  file_pmnu
						XmPushButtonGadget  exit_pbtn
			XmScrolledWindow  text_scrolled_windowSW
				XmScrollBar  HorScrollBar
				XmScrollBar  VertScrollBar
				XmText  text_scrolled_window
