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
#include "Dom/JsonObject.h"

namespace Gs2::Formation::Request
{
    class FGetFormByUserIdRequest;

    class GS2FORMATION_API FGetFormByUserIdRequest final : public TSharedFromThis<FGetFormByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> MoldModelNameValue;
        TOptional<int32> IndexValue;
        TOptional<FString> TimeOffsetTokenValue;
        
    public:
        
        FGetFormByUserIdRequest();
        FGetFormByUserIdRequest(
            const FGetFormByUserIdRequest& From
        );
        ~FGetFormByUserIdRequest() = default;

        TSharedPtr<FGetFormByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetFormByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetFormByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FGetFormByUserIdRequest> WithMoldModelName(const TOptional<FString> MoldModelName);
        TSharedPtr<FGetFormByUserIdRequest> WithIndex(const TOptional<int32> Index);
        TSharedPtr<FGetFormByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetMoldModelName() const;
        TOptional<int32> GetIndex() const;
        FString GetIndexString() const;
        TOptional<FString> GetTimeOffsetToken() const;

        static TSharedPtr<FGetFormByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetFormByUserIdRequest> FGetFormByUserIdRequestPtr;
}