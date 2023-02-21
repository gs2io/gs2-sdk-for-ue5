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
#include "../Model/Status.h"

namespace Gs2::Experience::Result
{
    class GS2EXPERIENCE_API FGetStatusWithSignatureResult final : public TSharedFromThis<FGetStatusWithSignatureResult>
    {
        TSharedPtr<Model::FStatus> ItemValue;
        TOptional<FString> BodyValue;
        TOptional<FString> SignatureValue;
        
    public:
        
        FGetStatusWithSignatureResult();
        FGetStatusWithSignatureResult(
            const FGetStatusWithSignatureResult& From
        );
        ~FGetStatusWithSignatureResult() = default;

        TSharedPtr<FGetStatusWithSignatureResult> WithItem(const TSharedPtr<Model::FStatus> Item);
        TSharedPtr<FGetStatusWithSignatureResult> WithBody(const TOptional<FString> Body);
        TSharedPtr<FGetStatusWithSignatureResult> WithSignature(const TOptional<FString> Signature);

        TSharedPtr<Model::FStatus> GetItem() const;
        TOptional<FString> GetBody() const;
        TOptional<FString> GetSignature() const;

        static TSharedPtr<FGetStatusWithSignatureResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetStatusWithSignatureResult, ESPMode::ThreadSafe> FGetStatusWithSignatureResultPtr;
}