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
#include "Account/Model/PlatformUser.h"

namespace Gs2::UE5::Account::Model
{
	class EZGS2_API FEzPlatformUser final : public TSharedFromThis<FEzPlatformUser>
	{
        TOptional<int32> TypeValue;
        TOptional<FString> UserIdentifierValue;
        TOptional<FString> UserIdValue;

	public:
        TSharedPtr<FEzPlatformUser> WithType(const TOptional<int32> Type);
        TSharedPtr<FEzPlatformUser> WithUserIdentifier(const TOptional<FString> UserIdentifier);
        TSharedPtr<FEzPlatformUser> WithUserId(const TOptional<FString> UserId);

        TOptional<int32> GetType() const;
        FString GetTypeString() const;

        TOptional<FString> GetUserIdentifier() const;

        TOptional<FString> GetUserId() const;

        Gs2::Account::Model::FPlatformUserPtr ToModel() const;
        static TSharedPtr<FEzPlatformUser> FromModel(Gs2::Account::Model::FPlatformUserPtr Model);
    };
    typedef TSharedPtr<FEzPlatformUser> FEzPlatformUserPtr;
}