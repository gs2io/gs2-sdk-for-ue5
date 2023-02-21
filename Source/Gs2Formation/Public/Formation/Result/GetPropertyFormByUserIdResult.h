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
#include "../Model/PropertyForm.h"
#include "../Model/FormModel.h"

namespace Gs2::Formation::Result
{
    class GS2FORMATION_API FGetPropertyFormByUserIdResult final : public TSharedFromThis<FGetPropertyFormByUserIdResult>
    {
        TSharedPtr<Model::FPropertyForm> ItemValue;
        TSharedPtr<Model::FFormModel> FormModelValue;
        
    public:
        
        FGetPropertyFormByUserIdResult();
        FGetPropertyFormByUserIdResult(
            const FGetPropertyFormByUserIdResult& From
        );
        ~FGetPropertyFormByUserIdResult() = default;

        TSharedPtr<FGetPropertyFormByUserIdResult> WithItem(const TSharedPtr<Model::FPropertyForm> Item);
        TSharedPtr<FGetPropertyFormByUserIdResult> WithFormModel(const TSharedPtr<Model::FFormModel> FormModel);

        TSharedPtr<Model::FPropertyForm> GetItem() const;
        TSharedPtr<Model::FFormModel> GetFormModel() const;

        static TSharedPtr<FGetPropertyFormByUserIdResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetPropertyFormByUserIdResult, ESPMode::ThreadSafe> FGetPropertyFormByUserIdResultPtr;
}