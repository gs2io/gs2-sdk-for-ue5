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
#include "../Model/NodeModelMaster.h"

namespace Gs2::SkillTree::Result
{
    class GS2SKILLTREE_API FCreateNodeModelMasterResult final : public TSharedFromThis<FCreateNodeModelMasterResult>
    {
        TSharedPtr<Model::FNodeModelMaster> ItemValue;
        
    public:
        
        FCreateNodeModelMasterResult();
        FCreateNodeModelMasterResult(
            const FCreateNodeModelMasterResult& From
        );
        ~FCreateNodeModelMasterResult() = default;

        TSharedPtr<FCreateNodeModelMasterResult> WithItem(const TSharedPtr<Model::FNodeModelMaster> Item);

        TSharedPtr<Model::FNodeModelMaster> GetItem() const;

        static TSharedPtr<FCreateNodeModelMasterResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateNodeModelMasterResult, ESPMode::ThreadSafe> FCreateNodeModelMasterResultPtr;
}