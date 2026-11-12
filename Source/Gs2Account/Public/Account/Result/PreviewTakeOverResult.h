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
    class GS2ACCOUNT_API FPreviewTakeOverResult final : public TSharedFromThis<FPreviewTakeOverResult>
    {
        TSharedPtr<Model::FAccount> ItemValue;
        TSharedPtr<TArray<TSharedPtr<Model::FBanStatus>>> BanStatusesValue;
        TOptional<FString> TokenValue;
        TOptional<int64> ExpireValue;
        
    public:
        
        FPreviewTakeOverResult();
        FPreviewTakeOverResult(
            const FPreviewTakeOverResult& From
        );
        ~FPreviewTakeOverResult() = default;

        TSharedPtr<FPreviewTakeOverResult> WithItem(const TSharedPtr<Model::FAccount> Item);
        TSharedPtr<FPreviewTakeOverResult> WithBanStatuses(const TSharedPtr<TArray<TSharedPtr<Model::FBanStatus>>> BanStatuses);
        TSharedPtr<FPreviewTakeOverResult> WithToken(const TOptional<FString> Token);
        TSharedPtr<FPreviewTakeOverResult> WithExpire(const TOptional<int64> Expire);

        TSharedPtr<Model::FAccount> GetItem() const;
        TSharedPtr<TArray<TSharedPtr<Model::FBanStatus>>> GetBanStatuses() const;
        TOptional<FString> GetToken() const;
        TOptional<int64> GetExpire() const;
        FString GetExpireString() const;

        static TSharedPtr<FPreviewTakeOverResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FPreviewTakeOverResult, ESPMode::ThreadSafe> FPreviewTakeOverResultPtr;
}