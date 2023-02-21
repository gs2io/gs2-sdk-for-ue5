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
#include "../Model/Form.h"
#include "../Model/Mold.h"
#include "../Model/MoldModel.h"
#include "../Model/FormModel.h"

namespace Gs2::Formation::Result
{
    class GS2FORMATION_API FGetFormResult final : public TSharedFromThis<FGetFormResult>
    {
        TSharedPtr<Model::FForm> ItemValue;
        TSharedPtr<Model::FMold> MoldValue;
        TSharedPtr<Model::FMoldModel> MoldModelValue;
        TSharedPtr<Model::FFormModel> FormModelValue;
        
    public:
        
        FGetFormResult();
        FGetFormResult(
            const FGetFormResult& From
        );
        ~FGetFormResult() = default;

        TSharedPtr<FGetFormResult> WithItem(const TSharedPtr<Model::FForm> Item);
        TSharedPtr<FGetFormResult> WithMold(const TSharedPtr<Model::FMold> Mold);
        TSharedPtr<FGetFormResult> WithMoldModel(const TSharedPtr<Model::FMoldModel> MoldModel);
        TSharedPtr<FGetFormResult> WithFormModel(const TSharedPtr<Model::FFormModel> FormModel);

        TSharedPtr<Model::FForm> GetItem() const;
        TSharedPtr<Model::FMold> GetMold() const;
        TSharedPtr<Model::FMoldModel> GetMoldModel() const;
        TSharedPtr<Model::FFormModel> GetFormModel() const;

        static TSharedPtr<FGetFormResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetFormResult, ESPMode::ThreadSafe> FGetFormResultPtr;
}