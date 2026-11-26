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
    class FVerifyFormByUserIdRequest;

    class GS2FORMATION_API FVerifyFormByUserIdRequest final : public TSharedFromThis<FVerifyFormByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> MoldModelNameValue;
        TOptional<int32> IndexValue;
        TOptional<FString> SlotNameValue;
        TOptional<FString> PropertyIdRegexValue;
        TOptional<FString> CountTypeValue;
        TOptional<FString> VerifyTypeValue;
        TOptional<int32> CountValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FVerifyFormByUserIdRequest();
        FVerifyFormByUserIdRequest(
            const FVerifyFormByUserIdRequest& From
        );
        ~FVerifyFormByUserIdRequest() = default;

        TSharedPtr<FVerifyFormByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FVerifyFormByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FVerifyFormByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FVerifyFormByUserIdRequest> WithMoldModelName(const TOptional<FString> MoldModelName);
        TSharedPtr<FVerifyFormByUserIdRequest> WithIndex(const TOptional<int32> Index);
        TSharedPtr<FVerifyFormByUserIdRequest> WithSlotName(const TOptional<FString> SlotName);
        TSharedPtr<FVerifyFormByUserIdRequest> WithPropertyIdRegex(const TOptional<FString> PropertyIdRegex);
        TSharedPtr<FVerifyFormByUserIdRequest> WithCountType(const TOptional<FString> CountType);
        TSharedPtr<FVerifyFormByUserIdRequest> WithVerifyType(const TOptional<FString> VerifyType);
        TSharedPtr<FVerifyFormByUserIdRequest> WithCount(const TOptional<int32> Count);
        TSharedPtr<FVerifyFormByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FVerifyFormByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetMoldModelName() const;
        TOptional<int32> GetIndex() const;
        FString GetIndexString() const;
        TOptional<FString> GetSlotName() const;
        TOptional<FString> GetPropertyIdRegex() const;
        TOptional<FString> GetCountType() const;
        TOptional<FString> GetVerifyType() const;
        TOptional<int32> GetCount() const;
        FString GetCountString() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FVerifyFormByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FVerifyFormByUserIdRequest> FVerifyFormByUserIdRequestPtr;
}