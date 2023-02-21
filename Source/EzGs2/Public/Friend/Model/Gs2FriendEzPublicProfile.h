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
#include "Friend/Model/PublicProfile.h"

namespace Gs2::UE5::Friend::Model
{
	class EZGS2_API FEzPublicProfile final : public TSharedFromThis<FEzPublicProfile>
	{
        TOptional<FString> UserIdValue;
        TOptional<FString> PublicProfileValue;

	public:
        TSharedPtr<FEzPublicProfile> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FEzPublicProfile> WithPublicProfile(const TOptional<FString> PublicProfile);

        TOptional<FString> GetUserId() const;

        TOptional<FString> GetPublicProfile() const;

        Gs2::Friend::Model::FPublicProfilePtr ToModel() const;
        static TSharedPtr<FEzPublicProfile> FromModel(Gs2::Friend::Model::FPublicProfilePtr Model);
    };
    typedef TSharedPtr<FEzPublicProfile> FEzPublicProfilePtr;
}