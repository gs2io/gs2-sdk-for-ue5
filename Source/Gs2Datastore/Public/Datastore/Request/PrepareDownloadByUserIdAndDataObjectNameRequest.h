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
    class FPrepareDownloadByUserIdAndDataObjectNameRequest;

    class GS2DATASTORE_API FPrepareDownloadByUserIdAndDataObjectNameRequest final : public TSharedFromThis<FPrepareDownloadByUserIdAndDataObjectNameRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> DataObjectNameValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FPrepareDownloadByUserIdAndDataObjectNameRequest();
        FPrepareDownloadByUserIdAndDataObjectNameRequest(
            const FPrepareDownloadByUserIdAndDataObjectNameRequest& From
        );
        ~FPrepareDownloadByUserIdAndDataObjectNameRequest() = default;

        TSharedPtr<FPrepareDownloadByUserIdAndDataObjectNameRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FPrepareDownloadByUserIdAndDataObjectNameRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FPrepareDownloadByUserIdAndDataObjectNameRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FPrepareDownloadByUserIdAndDataObjectNameRequest> WithDataObjectName(const TOptional<FString> DataObjectName);
        TSharedPtr<FPrepareDownloadByUserIdAndDataObjectNameRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FPrepareDownloadByUserIdAndDataObjectNameRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetDataObjectName() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FPrepareDownloadByUserIdAndDataObjectNameRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FPrepareDownloadByUserIdAndDataObjectNameRequest> FPrepareDownloadByUserIdAndDataObjectNameRequestPtr;
}