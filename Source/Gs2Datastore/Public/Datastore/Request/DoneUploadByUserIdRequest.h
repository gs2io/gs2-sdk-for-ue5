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

namespace Gs2::Datastore::Request
{
    class FDoneUploadByUserIdRequest;

    class GS2DATASTORE_API FDoneUploadByUserIdRequest final : public TSharedFromThis<FDoneUploadByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> DataObjectNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FDoneUploadByUserIdRequest();
        FDoneUploadByUserIdRequest(
            const FDoneUploadByUserIdRequest& From
        );
        ~FDoneUploadByUserIdRequest() = default;

        TSharedPtr<FDoneUploadByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDoneUploadByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDoneUploadByUserIdRequest> WithDataObjectName(const TOptional<FString> DataObjectName);
        TSharedPtr<FDoneUploadByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FDoneUploadByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FDoneUploadByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetDataObjectName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FDoneUploadByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDoneUploadByUserIdRequest> FDoneUploadByUserIdRequestPtr;
}