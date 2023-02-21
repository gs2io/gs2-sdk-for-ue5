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

namespace Gs2::Account::Model
{
    class GS2ACCOUNT_API FDataOwner final : public TSharedFromThis<FDataOwner>
    {
        TOptional<FString> DataOwnerIdValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> NameValue;
        TOptional<int64> CreatedAtValue;

    public:
        FDataOwner();
        FDataOwner(
            const FDataOwner& From
        );
        ~FDataOwner() = default;

        TSharedPtr<FDataOwner> WithDataOwnerId(const TOptional<FString> DataOwnerId);
        TSharedPtr<FDataOwner> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FDataOwner> WithName(const TOptional<FString> Name);
        TSharedPtr<FDataOwner> WithCreatedAt(const TOptional<int64> CreatedAt);

        TOptional<FString> GetDataOwnerId() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetName() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetUserIdFromGrn(const FString Grn);
        static TOptional<FString> GetDataOwnerNameFromGrn(const FString Grn);

        static TSharedPtr<FDataOwner> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FDataOwner, ESPMode::ThreadSafe> FDataOwnerPtr;
}