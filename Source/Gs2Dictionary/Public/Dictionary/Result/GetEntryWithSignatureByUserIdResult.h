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
#include "../Model/Entry.h"

namespace Gs2::Dictionary::Result
{
    class GS2DICTIONARY_API FGetEntryWithSignatureByUserIdResult final : public TSharedFromThis<FGetEntryWithSignatureByUserIdResult>
    {
        TSharedPtr<Model::FEntry> ItemValue;
        TOptional<FString> BodyValue;
        TOptional<FString> SignatureValue;
        
    public:
        
        FGetEntryWithSignatureByUserIdResult();
        FGetEntryWithSignatureByUserIdResult(
            const FGetEntryWithSignatureByUserIdResult& From
        );
        ~FGetEntryWithSignatureByUserIdResult() = default;

        TSharedPtr<FGetEntryWithSignatureByUserIdResult> WithItem(const TSharedPtr<Model::FEntry> Item);
        TSharedPtr<FGetEntryWithSignatureByUserIdResult> WithBody(const TOptional<FString> Body);
        TSharedPtr<FGetEntryWithSignatureByUserIdResult> WithSignature(const TOptional<FString> Signature);

        TSharedPtr<Model::FEntry> GetItem() const;
        TOptional<FString> GetBody() const;
        TOptional<FString> GetSignature() const;

        static TSharedPtr<FGetEntryWithSignatureByUserIdResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetEntryWithSignatureByUserIdResult, ESPMode::ThreadSafe> FGetEntryWithSignatureByUserIdResultPtr;
}