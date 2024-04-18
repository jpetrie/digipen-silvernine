object frmSPRC: TfrmSPRC
  Left = 289
  Top = 236
  HorzScrollBar.Visible = False
  VertScrollBar.Visible = False
  BorderStyle = bsSingle
  Caption = 'Sprite Collections'
  ClientHeight = 447
  ClientWidth = 906
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsMDIForm
  OldCreateOrder = False
  Scaled = False
  OnActivate = FormActivate
  OnClose = FormClose
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnPaint = FormPaint
  OnResize = FormResize
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object txtSPRCSequences: TLabel
    Left = 24
    Top = 16
    Width = 87
    Height = 13
    Hint = 'Sprites in the sequence'
    Caption = 'Sprite Sequences:'
  end
  object txtSPRCImages: TLabel
    Left = 360
    Top = 16
    Width = 130
    Height = 13
    Caption = 'Sequence images(ordered):'
  end
  object txtSPRCFrames: TLabel
    Left = 600
    Top = 16
    Width = 6
    Height = 13
    Caption = '0'
  end
  object txtSPRCFacings: TLabel
    Left = 280
    Top = 32
    Width = 40
    Height = 13
    Caption = 'Facings:'
  end
  object txtSPRCWidth: TLabel
    Left = 280
    Top = 80
    Width = 63
    Height = 13
    Caption = 'Image Width:'
  end
  object txtSPRCHeight: TLabel
    Left = 280
    Top = 128
    Width = 66
    Height = 13
    Caption = 'Image Height:'
  end
  object txtSPRCSequenceCount: TLabel
    Left = 264
    Top = 16
    Width = 6
    Height = 13
    Caption = '0'
  end
  object Bevel1: TBevel
    Left = 632
    Top = 336
    Width = 49
    Height = 49
  end
  object imgSPRCAlphaPicker: TImage
    Left = 634
    Top = 338
    Width = 44
    Height = 44
    IncrementalDisplay = True
    OnDblClick = imgSPRCAlphaPickerDblClick
  end
  object lblSPRCAlphaIgnore: TLabel
    Left = 632
    Top = 320
    Width = 90
    Height = 13
    Caption = 'Alpha Ignore Color:'
  end
  object lblSPRCBlend: TLabel
    Left = 631
    Top = 392
    Width = 27
    Height = 13
    Caption = 'Blend'
  end
  object lstSPRCSequences: TListBox
    Left = 24
    Top = 32
    Width = 249
    Height = 369
    Hint = 'Sprite sequences in the Sprite collection'
    ItemHeight = 13
    TabOrder = 1
    OnClick = lstSPRCSequencesClick
  end
  object btnSPRCNewSequence: TButton
    Left = 24
    Top = 400
    Width = 121
    Height = 25
    Hint = 'Add a new Sprite sequence to the collection'
    Caption = 'New Sequence'
    TabOrder = 0
    OnClick = btnSPRCNewSequenceClick
    OnMouseUp = btnSPRCNewSequenceMouseUp
  end
  object btnSPRCRemoveSequence: TButton
    Left = 144
    Top = 400
    Width = 131
    Height = 25
    Hint = 'Remove a Sprite sequence from the collection'
    Caption = 'Remove Sequence'
    TabOrder = 2
    OnClick = btnSPRCRemoveSequenceClick
  end
  object lstSPRCSequenceImages: TListBox
    Left = 360
    Top = 32
    Width = 249
    Height = 369
    Hint = 'Sprite sequences in the Sprite collection'
    ItemHeight = 13
    TabOrder = 3
    OnClick = lstSPRCSequenceImagesClick
  end
  object btnSPRCNewSequenceImage: TButton
    Left = 360
    Top = 400
    Width = 121
    Height = 25
    Hint = 'Add a new image to the Sprite sequence '
    Caption = 'New Image'
    TabOrder = 4
    OnClick = btnSPRCNewSequenceImageClick
  end
  object btnSPRCRemoveSequenceImage: TButton
    Left = 480
    Top = 400
    Width = 129
    Height = 25
    Hint = 'Remove an image from a Sprite sequence '
    Caption = 'Remove Sequence'
    TabOrder = 5
    OnClick = btnSPRCRemoveSequenceImageClick
  end
  object editSPRCFacings: TEdit
    Left = 280
    Top = 48
    Width = 33
    Height = 21
    TabOrder = 6
    Text = '0'
    OnChange = editSPRCFacingsChange
  end
  object editSPRCFrameWidth: TEdit
    Left = 280
    Top = 96
    Width = 33
    Height = 21
    TabOrder = 7
    Text = '0'
    OnChange = editSPRCFrameWidthChange
  end
  object editSPRCFrameHeight: TEdit
    Left = 280
    Top = 144
    Width = 33
    Height = 21
    TabOrder = 8
    Text = '0'
    OnChange = editSPRCFrameHeightChange
  end
  object spnSPRCFacings: TUpDown
    Left = 313
    Top = 48
    Width = 15
    Height = 21
    Associate = editSPRCFacings
    Min = 0
    Position = 0
    TabOrder = 9
    Wrap = False
  end
  object spnSPRCWidth: TUpDown
    Left = 313
    Top = 96
    Width = 15
    Height = 21
    Associate = editSPRCFrameWidth
    Min = 0
    Position = 0
    TabOrder = 10
    Wrap = False
  end
  object spnSPRCHeight: TUpDown
    Left = 313
    Top = 144
    Width = 15
    Height = 21
    Associate = editSPRCFrameHeight
    Min = 0
    Position = 0
    TabOrder = 11
    Wrap = False
  end
  object pnlSPRCImagePreview: TPanel
    Left = 632
    Top = 32
    Width = 256
    Height = 256
    BevelOuter = bvLowered
    Caption = 'Image Preview'
    TabOrder = 12
  end
  object btnSPRCApply: TButton
    Left = 816
    Top = 328
    Width = 75
    Height = 25
    Caption = '&Apply'
    TabOrder = 13
    OnClick = btnSPRCApplyClick
  end
  object btnSPRCCancel: TButton
    Left = 816
    Top = 394
    Width = 75
    Height = 25
    Cancel = True
    Caption = '&Cancel'
    TabOrder = 14
    OnClick = btnSPRCCancelClick
  end
  object btnSPRCRevert: TButton
    Left = 816
    Top = 360
    Width = 75
    Height = 25
    Caption = 'Revert'
    TabOrder = 15
    OnClick = btnSPRCRevertClick
  end
  object txtSPRCAlphaRed: TStaticText
    Left = 688
    Top = 336
    Width = 27
    Height = 17
    Caption = 'Red:'
    TabOrder = 16
  end
  object txtSPRCAlphaGreen: TStaticText
    Left = 688
    Top = 352
    Width = 36
    Height = 17
    Caption = 'Green:'
    TabOrder = 17
  end
  object txtSPRCAlphaBlue: TStaticText
    Left = 688
    Top = 368
    Width = 28
    Height = 17
    Caption = 'Blue:'
    TabOrder = 18
  end
  object txtSPRCAlphaValueRed: TStaticText
    Left = 728
    Top = 336
    Width = 10
    Height = 17
    Caption = '0'
    TabOrder = 19
  end
  object txtSPRCAlphaValueGreen: TStaticText
    Left = 728
    Top = 352
    Width = 10
    Height = 17
    Caption = '0'
    TabOrder = 20
  end
  object txtSPRCAlphaValueBlue: TStaticText
    Left = 728
    Top = 368
    Width = 10
    Height = 17
    Caption = '0'
    TabOrder = 21
  end
  object chkSPRCBlend: TCheckBox
    Left = 666
    Top = 391
    Width = 17
    Height = 17
    TabOrder = 22
    OnClick = chkSPRCBlendClick
  end
  object trkSPRCBlend: TTrackBar
    Left = 624
    Top = 408
    Width = 150
    Height = 17
    Ctl3D = True
    Max = 255
    Orientation = trHorizontal
    ParentCtl3D = False
    Frequency = 1
    Position = 255
    SelEnd = 0
    SelStart = 0
    TabOrder = 23
    ThumbLength = 10
    TickMarks = tmBottomRight
    TickStyle = tsNone
    Visible = False
  end
  object OpenDialogSPRCBitmaps: TOpenDialog
    Filter = 'Bitmaps (*.bmp)|*.bmp'
    Options = [ofHideReadOnly]
    Left = 304
    Top = 384
  end
  object dlgAlphaPicker: TColorDialog
    Ctl3D = True
    OnClose = dlgAlphaPickerClose
    Left = 304
    Top = 336
  end
end
