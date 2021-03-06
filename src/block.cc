#include "block.h"

#include <ctime>
#include <string>

#include "sha256.h"

namespace simplechain {

Block::Block(Block* previous_block, std::string data, int difficulty,
             std::time_t timestamp, int nonce) {
  index_ = previous_block ? previous_block->index() + 1 : 0;
  previous_block_ = previous_block;
  data_ = data;
  difficulty_ = difficulty;
  timestamp_ = timestamp ? timestamp : std::time(nullptr);
  nonce_ = nonce;
  hash_ = CalculateHash();
}

int Block::index() const { return index_; }

Block* Block::previous_block() const { return previous_block_; }

std::string Block::data() const { return data_; }

int Block::difficulty() const { return difficulty_; }

std::time_t Block::timestamp() const { return timestamp_; }

int Block::nonce() const { return nonce_; }

std::string Block::header() const {
  const std::string previous_block_hash =
      previous_block_ ? previous_block_->hash() : "";
  const std::string data_hash = sha256(data_);
  return previous_block_hash + data_hash + std::to_string(difficulty_) +
         std::to_string(timestamp_) + std::to_string(nonce_);
}

std::string Block::hash() const { return hash_; }

void Block::inc_nonce() { nonce_++; }

void Block::set_hash(std::string hash) { hash_ = hash; }

std::string Block::CalculateHash() const { return sha256(header()); }

bool Block::IsValid() const {
  if (hash_ != CalculateHash()) {
    return false;
  }

  if (hash_.substr(0, difficulty_) != std::string(difficulty_, '0')) {
    return false;
  }

  return true;
}

}  // namespace simplechain
