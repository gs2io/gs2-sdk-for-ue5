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
#include "Gateway/Model/FirebaseToken.h"

namespace Gs2::UE5::Gateway::Model
{
	class EZGS2_API FEzFirebaseToken final : public TSharedFromThis<FEzFirebaseToken>
	{
        TOptional<FString> UserIdValue;
        TOptional<FString> TokenValue;
        TOptional<FString> LocaleValue;

	public:
        TSharedPtr<FEzFirebaseToken> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FEzFirebaseToken> WithToken(const TOptional<FString> Token);
        TSharedPtr<FEzFirebaseToken> WithLocale(const TOptional<FString> Locale);

        TOptional<FString> GetUserId() const;

        TOptional<FString> GetToken() const;

        TOptional<FString> GetLocale() const;

        Gs2::Gateway::Model::FFirebaseTokenPtr ToModel() const;
        static TSharedPtr<FEzFirebaseToken> FromModel(Gs2::Gateway::Model::FFirebaseTokenPtr Model);
    };
    typedef TSharedPtr<FEzFirebaseToken> FEzFirebaseTokenPtr;
}