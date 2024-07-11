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
#include "Account/Model/PlatformId.h"

namespace Gs2::UE5::Account::Model
{
	class EZGS2_API FEzPlatformId final : public TSharedFromThis<FEzPlatformId>
	{
        TOptional<int32> TypeValue;
        TOptional<FString> UserIdentifierValue;
        TOptional<FString> UserIdValue;
        TOptional<int64> CreatedAtValue;

	public:
        TSharedPtr<FEzPlatformId> WithType(const TOptional<int32> Type);
        TSharedPtr<FEzPlatformId> WithUserIdentifier(const TOptional<FString> UserIdentifier);
        TSharedPtr<FEzPlatformId> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FEzPlatformId> WithCreatedAt(const TOptional<int64> CreatedAt);

        TOptional<int32> GetType() const;
        FString GetTypeString() const;

        TOptional<FString> GetUserIdentifier() const;

        TOptional<FString> GetUserId() const;

        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;

        Gs2::Account::Model::FPlatformIdPtr ToModel() const;
        static TSharedPtr<FEzPlatformId> FromModel(Gs2::Account::Model::FPlatformIdPtr Model);
    };
    typedef TSharedPtr<FEzPlatformId> FEzPlatformIdPtr;
}