/*
 * Copyright 2016 Game Server Services, Inc. or its affiliates. All Rights
 * Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#pragma once

#include "CoreMinimal.h"
#include "../Model/VersionModelMaster.h"

namespace Gs2::Version::Result
{
    class GS2VERSION_API FDeleteVersionModelMasterResult final : public TSharedFromThis<FDeleteVersionModelMasterResult>
    {
        TSharedPtr<Model::FVersionModelMaster> ItemValue;
        
    public:
        
        FDeleteVersionModelMasterResult();
        FDeleteVersionModelMasterResult(
            const FDeleteVersionModelMasterResult& From
        );
        ~FDeleteVersionModelMasterResult() = default;

        TSharedPtr<FDeleteVersionModelMasterResult> WithItem(const TSharedPtr<Model::FVersionModelMaster> Item);

        TSharedPtr<Model::FVersionModelMaster> GetItem() const;

        static TSharedPtr<FDeleteVersionModelMasterResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDeleteVersionModelMasterResult, ESPMode::ThreadSafe> FDeleteVersionModelMasterResultPtr;
}