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
#include "../Model/PropertyFormModel.h"

namespace Gs2::Formation::Result
{
    class GS2FORMATION_API FSetPropertyFormResult final : public TSharedFromThis<FSetPropertyFormResult>
    {
        TSharedPtr<Model::FPropertyForm> ItemValue;
        TSharedPtr<Model::FPropertyFormModel> PropertyFormModelValue;
        
    public:
        
        FSetPropertyFormResult();
        FSetPropertyFormResult(
            const FSetPropertyFormResult& From
        );
        ~FSetPropertyFormResult() = default;

        TSharedPtr<FSetPropertyFormResult> WithItem(const TSharedPtr<Model::FPropertyForm> Item);
        TSharedPtr<FSetPropertyFormResult> WithPropertyFormModel(const TSharedPtr<Model::FPropertyFormModel> PropertyFormModel);

        TSharedPtr<Model::FPropertyForm> GetItem() const;
        TSharedPtr<Model::FPropertyFormModel> GetPropertyFormModel() const;

        static TSharedPtr<FSetPropertyFormResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FSetPropertyFormResult, ESPMode::ThreadSafe> FSetPropertyFormResultPtr;
}