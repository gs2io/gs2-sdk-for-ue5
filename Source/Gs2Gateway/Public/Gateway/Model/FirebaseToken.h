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

namespace Gs2::Gateway::Model
{
    class GS2GATEWAY_API FFirebaseToken final : public Gs2Object, public TSharedFromThis<FFirebaseToken>
    {
        TOptional<FString> FirebaseTokenIdValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> TokenValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;

    public:
        FFirebaseToken();
        FFirebaseToken(
            const FFirebaseToken& From
        );
        virtual ~FFirebaseToken() override = default;

        TSharedPtr<FFirebaseToken> WithFirebaseTokenId(const TOptional<FString> FirebaseTokenId);
        TSharedPtr<FFirebaseToken> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FFirebaseToken> WithToken(const TOptional<FString> Token);
        TSharedPtr<FFirebaseToken> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FFirebaseToken> WithUpdatedAt(const TOptional<int64> UpdatedAt);

        TOptional<FString> GetFirebaseTokenId() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetToken() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetUserIdFromGrn(const FString Grn);

        static TSharedPtr<FFirebaseToken> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FFirebaseToken, ESPMode::ThreadSafe> FFirebaseTokenPtr;
}