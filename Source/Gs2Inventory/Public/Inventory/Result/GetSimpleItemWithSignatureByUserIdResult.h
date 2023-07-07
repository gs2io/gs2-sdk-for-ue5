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
#include "../Model/SimpleItem.h"
#include "../Model/SimpleItemModel.h"

namespace Gs2::Inventory::Result
{
    class GS2INVENTORY_API FGetSimpleItemWithSignatureByUserIdResult final : public TSharedFromThis<FGetSimpleItemWithSignatureByUserIdResult>
    {
        TSharedPtr<Model::FSimpleItem> ItemValue;
        TSharedPtr<Model::FSimpleItemModel> SimpleItemModelValue;
        TOptional<FString> BodyValue;
        TOptional<FString> SignatureValue;
        
    public:
        
        FGetSimpleItemWithSignatureByUserIdResult();
        FGetSimpleItemWithSignatureByUserIdResult(
            const FGetSimpleItemWithSignatureByUserIdResult& From
        );
        ~FGetSimpleItemWithSignatureByUserIdResult() = default;

        TSharedPtr<FGetSimpleItemWithSignatureByUserIdResult> WithItem(const TSharedPtr<Model::FSimpleItem> Item);
        TSharedPtr<FGetSimpleItemWithSignatureByUserIdResult> WithSimpleItemModel(const TSharedPtr<Model::FSimpleItemModel> SimpleItemModel);
        TSharedPtr<FGetSimpleItemWithSignatureByUserIdResult> WithBody(const TOptional<FString> Body);
        TSharedPtr<FGetSimpleItemWithSignatureByUserIdResult> WithSignature(const TOptional<FString> Signature);

        TSharedPtr<Model::FSimpleItem> GetItem() const;
        TSharedPtr<Model::FSimpleItemModel> GetSimpleItemModel() const;
        TOptional<FString> GetBody() const;
        TOptional<FString> GetSignature() const;

        static TSharedPtr<FGetSimpleItemWithSignatureByUserIdResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetSimpleItemWithSignatureByUserIdResult, ESPMode::ThreadSafe> FGetSimpleItemWithSignatureByUserIdResultPtr;
}