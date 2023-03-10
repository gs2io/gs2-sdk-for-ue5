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

namespace Gs2::Exchange::Model
{
    class GS2EXCHANGE_API FAwait final : public TSharedFromThis<FAwait>
    {
        TOptional<FString> AwaitIdValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> RateNameValue;
        TOptional<FString> NameValue;
        TOptional<int32> CountValue;
        TOptional<int64> ExchangedAtValue;

    public:
        FAwait();
        FAwait(
            const FAwait& From
        );
        ~FAwait() = default;

        TSharedPtr<FAwait> WithAwaitId(const TOptional<FString> AwaitId);
        TSharedPtr<FAwait> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FAwait> WithRateName(const TOptional<FString> RateName);
        TSharedPtr<FAwait> WithName(const TOptional<FString> Name);
        TSharedPtr<FAwait> WithCount(const TOptional<int32> Count);
        TSharedPtr<FAwait> WithExchangedAt(const TOptional<int64> ExchangedAt);

        TOptional<FString> GetAwaitId() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetRateName() const;
        TOptional<FString> GetName() const;
        TOptional<int32> GetCount() const;
        FString GetCountString() const;
        TOptional<int64> GetExchangedAt() const;
        FString GetExchangedAtString() const;

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