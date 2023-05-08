#pragma once

#include "nfc_app.h"

#include <furi.h>
#include <furi_hal.h>

#include <gui/gui.h>
#include <gui/view.h>
#include <assets_icons.h>
#include <gui/view_dispatcher.h>
#include <gui/scene_manager.h>
#include <cli/cli.h>
#include <notification/notification_messages.h>

#include <gui/modules/submenu.h>
#include <gui/modules/dialog_ex.h>
#include <gui/modules/popup.h>
#include <gui/modules/loading.h>
#include <gui/modules/text_input.h>
#include <gui/modules/byte_input.h>
#include <gui/modules/text_box.h>
#include <gui/modules/widget.h>

#include <lib/nfc/nfc_types.h>
#include <lib/nfc/nfc_worker.h>
#include <lib/nfc/nfc_device.h>
#include <lib/nfc/helpers/mf_classic_dict.h>
#include <lib/nfc/parsers/nfc_supported_card.h>
#include <lib/nfc/helpers/nfc_generators.h>

#include "views/dict_attack.h"
#include "views/detect_reader.h"

#include <nfc/scenes/nfc_scene.h>
#include <nfc/helpers/nfc_custom_event.h>

#include <dialogs/dialogs.h>

#include "rpc/rpc_app.h"

#include <m-array.h>

ARRAY_DEF(MfClassicUserKeys, char*, M_PTR_OPLIST);

#define NFC_TEXT_STORE_SIZE 128
#define NFC_APP_FOLDER ANY_PATH("nfc")

typedef enum {
    NfcRpcStateIdle,
    NfcRpcStateEmulating,
    NfcRpcStateEmulated,
} NfcRpcState;

struct NfcApp {
    NfcWorker* worker;
    ViewDispatcher* view_dispatcher;
    Gui* gui;
    NotificationApp* notifications;
    SceneManager* scene_manager;
    NfcDevice* dev;
    FuriHalNfcDevData dev_edit_data;

    char text_store[NFC_TEXT_STORE_SIZE + 1];
    FuriString* text_box_store;
    uint8_t byte_input_store[6];
    MfClassicUserKeys_t mfc_key_strs; // Used in MFC key listing

    void* rpc_ctx;
    NfcRpcState rpc_state;

    // Common Views
    Submenu* submenu;
    DialogEx* dialog_ex;
    Popup* popup;
    Loading* loading;
    TextInput* text_input;
    ByteInput* byte_input;
    TextBox* text_box;
    Widget* widget;
    DictAttack* dict_attack;
    DetectReader* detect_reader;

    const NfcGenerator* generator;
};

typedef enum {
    NfcViewMenu,
    NfcViewDialogEx,
    NfcViewPopup,
    NfcViewLoading,
    NfcViewTextInput,
    NfcViewByteInput,
    NfcViewTextBox,
    NfcViewWidget,
    NfcViewDictAttack,
    NfcViewDetectReader,
} NfcView;

NfcApp* nfc_alloc();

int32_t nfc_task(void* p);

void nfc_text_store_set(NfcApp* nfc, const char* text, ...);

void nfc_text_store_clear(NfcApp* nfc);

void nfc_blink_read_start(NfcApp* nfc);

void nfc_blink_emulate_start(NfcApp* nfc);

void nfc_blink_detect_start(NfcApp* nfc);

void nfc_blink_stop(NfcApp* nfc);

bool nfc_save_file(NfcApp* nfc);

void nfc_show_loading_popup(void* context, bool show);