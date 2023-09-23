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
#include "../Model/Account.h"
#include "../Model/BanStatus.h"

namespace Gs2::Account::Result
{
    class GS2ACCOUNT_API FAuthenticationResult final : public TSharedFromThis<FAuthenticationResult>
    {
        TSharedPtr<Model::FAccount> ItemValue;
        TSharedPtr<TArray<TSharedPtr<Model::FBanStatus>>> BanStatusesValue;
        TOptional<FString> BodyValue;
        TOptional<FString> SignatureValue;
        
    public:
        
        FAuthenticationResult();
        FAuthenticationResult(
            const FAuthenticationResult& From
        );
        ~FAuthenticationResult() = default;

        TSharedPtr<FAuthenticationResult> WithItem(const TSharedPtr<Model::FAccount> Item);
        TSharedPtr<FAuthenticationResult> WithBanStatuses(const TSharedPtr<TArray<TSharedPtr<Model::FBanStatus>>> BanStatuses);
        TSharedPtr<FAuthenticationResult> WithBody(const TOptional<FString> Body);
        TSharedPtr<FAuthenticationResult> WithSignature(const TOptional<FString> Signature);

        TSharedPtr<Model::FAccount> GetItem() const;
        TSharedPtr<TArray<TSharedPtr<Model::FBanStatus>>> GetBanStatuses() const;
        TOptional<FString> GetBody() const;
        TOptional<FString> GetSignature() const;

        static TSharedPtr<FAuthenticationResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FAuthenticationResult, ESPMode::ThreadSafe> FAuthenticationResultPtr;
}