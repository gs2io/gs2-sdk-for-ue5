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
    class GS2FORMATION_API FGetPropertyFormWithSignatureResult final : public TSharedFromThis<FGetPropertyFormWithSignatureResult>
    {
        TSharedPtr<Model::FPropertyForm> ItemValue;
        TOptional<FString> BodyValue;
        TOptional<FString> SignatureValue;
        TSharedPtr<Model::FPropertyFormModel> PropertyFormModelValue;
        
    public:
        
        FGetPropertyFormWithSignatureResult();
        FGetPropertyFormWithSignatureResult(
            const FGetPropertyFormWithSignatureResult& From
        );
        ~FGetPropertyFormWithSignatureResult() = default;

        TSharedPtr<FGetPropertyFormWithSignatureResult> WithItem(const TSharedPtr<Model::FPropertyForm> Item);
        TSharedPtr<FGetPropertyFormWithSignatureResult> WithBody(const TOptional<FString> Body);
        TSharedPtr<FGetPropertyFormWithSignatureResult> WithSignature(const TOptional<FString> Signature);
        TSharedPtr<FGetPropertyFormWithSignatureResult> WithPropertyFormModel(const TSharedPtr<Model::FPropertyFormModel> PropertyFormModel);

        TSharedPtr<Model::FPropertyForm> GetItem() const;
        TOptional<FString> GetBody() const;
        TOptional<FString> GetSignature() const;
        TSharedPtr<Model::FPropertyFormModel> GetPropertyFormModel() const;

        static TSharedPtr<FGetPropertyFormWithSignatureResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetPropertyFormWithSignatureResult, ESPMode::ThreadSafe> FGetPropertyFormWithSignatureResultPtr;
}