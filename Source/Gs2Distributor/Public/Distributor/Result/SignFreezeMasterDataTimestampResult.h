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

namespace Gs2::Distributor::Result
{
    class GS2DISTRIBUTOR_API FSignFreezeMasterDataTimestampResult final : public TSharedFromThis<FSignFreezeMasterDataTimestampResult>
    {
        TOptional<FString> BodyValue;
        TOptional<FString> SignatureValue;
        
    public:
        
        FSignFreezeMasterDataTimestampResult();
        FSignFreezeMasterDataTimestampResult(
            const FSignFreezeMasterDataTimestampResult& From
        );
        ~FSignFreezeMasterDataTimestampResult() = default;

        TSharedPtr<FSignFreezeMasterDataTimestampResult> WithBody(const TOptional<FString> Body);
        TSharedPtr<FSignFreezeMasterDataTimestampResult> WithSignature(const TOptional<FString> Signature);

        TOptional<FString> GetBody() const;
        TOptional<FString> GetSignature() const;

        static TSharedPtr<FSignFreezeMasterDataTimestampResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FSignFreezeMasterDataTimestampResult, ESPMode::ThreadSafe> FSignFreezeMasterDataTimestampResultPtr;
}