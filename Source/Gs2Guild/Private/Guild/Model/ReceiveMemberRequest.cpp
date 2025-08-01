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

#include "Guild/Model/ReceiveMemberRequest.h"

namespace Gs2::Guild::Model
{
    FReceiveMemberRequest::FReceiveMemberRequest():
        UserIdValue(TOptional<FString>()),
        TargetGuildNameValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        CreatedAtValue(TOptional<int64>())
    {
    }

    FReceiveMemberRequest::FReceiveMemberRequest(
        const FReceiveMemberRequest& From
    ):
        UserIdValue(From.UserIdValue),
        TargetGuildNameValue(From.TargetGuildNameValue),
        MetadataValue(From.MetadataValue),
        CreatedAtValue(From.CreatedAtValue)
    {
    }

    TSharedPtr<FReceiveMemberRequest> FReceiveMemberRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FReceiveMemberRequest> FReceiveMemberRequest::WithTargetGuildName(
        const TOptional<FString> TargetGuildName
    )
    {
        this->TargetGuildNameValue = TargetGuildName;
        return SharedThis(this);
    }

    TSharedPtr<FReceiveMemberRequest> FReceiveMemberRequest::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FReceiveMemberRequest> FReceiveMemberRequest::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }
    TOptional<FString> FReceiveMemberRequest::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<FString> FReceiveMemberRequest::GetTargetGuildName() const
    {
        return TargetGuildNameValue;
    }
    TOptional<FString> FReceiveMemberRequest::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<int64> FReceiveMemberRequest::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FReceiveMemberRequest::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }

    TSharedPtr<FReceiveMemberRequest> FReceiveMemberRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FReceiveMemberRequest>()
            ->WithUserId(Data->HasField(ANSI_TO_TCHAR("userId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("userId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithTargetGuildName(Data->HasField(ANSI_TO_TCHAR("targetGuildName")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("targetGuildName"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithMetadata(Data->HasField(ANSI_TO_TCHAR("metadata")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("metadata"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithCreatedAt(Data->HasField(ANSI_TO_TCHAR("createdAt")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("createdAt"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FReceiveMemberRequest::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (TargetGuildNameValue.IsSet())
        {
            JsonRootObject->SetStringField("targetGuildName", TargetGuildNameValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (CreatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("createdAt", FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FReceiveMemberRequest::TypeName = "ReceiveMemberRequest";
}