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
#include "Core/Gs2Object.h"
#include "Config.h"

namespace Gs2::Exchange::Model
{
    class GS2EXCHANGE_API FAwait final : public Gs2Object, public TSharedFromThis<FAwait>
    {
        TOptional<FString> AwaitIdValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> RateNameValue;
        TOptional<FString> NameValue;
        TOptional<int32> CountValue;
        TSharedPtr<TArray<TSharedPtr<FConfig>>> ConfigValue;
        TOptional<int64> ExchangedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FAwait();
        FAwait(
            const FAwait& From
        );
        virtual ~FAwait() override = default;

        TSharedPtr<FAwait> WithAwaitId(const TOptional<FString> AwaitId);
        TSharedPtr<FAwait> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FAwait> WithRateName(const TOptional<FString> RateName);
        TSharedPtr<FAwait> WithName(const TOptional<FString> Name);
        TSharedPtr<FAwait> WithCount(const TOptional<int32> Count);
        TSharedPtr<FAwait> WithConfig(const TSharedPtr<TArray<TSharedPtr<FConfig>>> Config);
        TSharedPtr<FAwait> WithExchangedAt(const TOptional<int64> ExchangedAt);
        TSharedPtr<FAwait> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetAwaitId() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetRateName() const;
        TOptional<FString> GetName() const;
        TOptional<int32> GetCount() const;
        FString GetCountString() const;
        TSharedPtr<TArray<TSharedPtr<FConfig>>> GetConfig() const;
        TOptional<int64> GetExchangedAt() const;
        FString GetExchangedAtString() const;
        TOptional<int64> GetRevision() const;
        FString GetRevisionString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetUserIdFromGrn(const FString Grn);
        static TOptional<FString> GetAwaitNameFromGrn(const FString Grn);

        static TSharedPtr<FAwait> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FAwait, ESPMode::ThreadSafe> FAwaitPtr;
}