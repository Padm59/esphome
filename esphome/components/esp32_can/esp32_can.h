#pragma once

#ifdef USE_ESP32

#include "esphome/components/canbus/canbus.h"
#include "esphome/core/component.h"
#include <driver/twai.h>

namespace esphome {
namespace esp32_can {

class ESP32Can : public canbus::Canbus {
 public:
  void set_rx(int rx) { rx_ = rx; }
  void set_tx(int tx) { tx_ = tx; }
  void set_acceptance_code(uint32_t acceptance_code) { this->filter_config_.acceptance_code = acceptance_code; }
  void set_acceptance_mask(uint32_t acceptance_mask) { this->filter_config_.acceptance_mask = acceptance_mask; }
  void set_single_filter(bool single_filter) { this->filter_config_.single_filter = single_filter; }
  void set_tx_queue_len(uint32_t tx_queue_len) { this->tx_queue_len_ = tx_queue_len; }
  void set_rx_queue_len(uint32_t rx_queue_len) { this->rx_queue_len_ = rx_queue_len; }
  ESP32Can(){};

 protected:
  bool setup_internal() override;
  canbus::Error send_message(struct canbus::CanFrame *frame) override;
  canbus::Error read_message(struct canbus::CanFrame *frame) override;

  int rx_{-1};
  int tx_{-1};
  twai_filter_config_t filter_config_;
  // uint32_t acceptance_code_;
  // uint32_t acceptance_mask_;
  // bool     single_filter_;
  optional<uint32_t> tx_queue_len_{};
  optional<uint32_t> rx_queue_len_{};
};

}  // namespace esp32_can
}  // namespace esphome

#endif
