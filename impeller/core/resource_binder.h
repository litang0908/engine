// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include <map>
#include <memory>
#include <optional>
#include <string>

#include "flutter/fml/logging.h"
#include "impeller/core/buffer_view.h"
#include "impeller/core/formats.h"
#include "impeller/core/sampler.h"
#include "impeller/core/shader_types.h"
#include "impeller/core/texture.h"

namespace impeller {

//------------------------------------------------------------------------------
/// @brief      An interface for binding resources. This is implemented by
///             |Command| and |ComputeCommand| to make GPU resources available
///             to a given command's pipeline.
///
struct ResourceBinder {
  virtual ~ResourceBinder() = default;

  virtual bool BindResource(ShaderStage stage,
                            const ShaderUniformSlot& slot,
                            const ShaderMetadata& metadata,
                            BufferView view) = 0;

  virtual bool BindResource(ShaderStage stage,
                            const SampledImageSlot& slot,
                            const ShaderMetadata& metadata,
                            std::shared_ptr<const Texture> texture,
                            std::shared_ptr<const Sampler> sampler) = 0;
};

}  // namespace impeller
