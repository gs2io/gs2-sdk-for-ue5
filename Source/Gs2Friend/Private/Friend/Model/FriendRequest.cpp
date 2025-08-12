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

#include "Friend/Model/FriendRequest.h"

namespace Gs2::Friend::Model
{
    FFriendRequest::FFriendRequest():
        UserIdValue(TOptional<FString>()),
        TargetUserIdValue(TOptional<FString>()),
        PublicProfileValue(TOptional<FString>())
    {
    }

    FFriendRequest::FFriendRequest(
        const FFriendRequest& From
    ):
        UserIdValue(From.UserIdValue),
        TargetUserIdValue(From.TargetUserIdValue),
        PublicProfileValue(From.PublicProfileValue)
    {
    }

    TSharedPtr<FFriendRequest> FFriendRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FFriendRequest> FFriendRequest::WithTargetUserId(
        const TOptional<FString> TargetUserId
    )
    {
        this->TargetUserIdValue = TargetUserId;
        return SharedThis(this);
    }

    TSharedPtr<FFriendRequest> FFriendRequest::WithPublicProfile(
        const TOptional<FString> PublicProfile
    )
    {
        this->PublicProfileValue = PublicProfile;
        return SharedThis(this);
    }
    TOptional<FString> FFriendRequest::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<FString> FFriendRequest::GetTargetUserId() const
    {
        return TargetUserIdValue;
    }
    TOptional<FString> FFriendRequest::GetPublicProfile() const
    {
        return PublicProfileValue;
    }

    TSharedPtr<FFriendRequest> FFriendRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FFriendRequest>()
            ->WithUserId(Data->HasField(ANSI_TO_TCHAR("userId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("userId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithTargetUserId(Data->HasField(ANSI_TO_TCHAR("targetUserId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("targetUserId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithPublicProfile(Data->HasField(ANSI_TO_TCHAR("publicProfile")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("publicProfile"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FFriendRequest::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (TargetUserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("targetUserId", TargetUserIdValue.GetValue());
        }
        if (PublicProfileValue.IsSet())
        {
            JsonRootObject->SetStringField("publicProfile", PublicProfileValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FFriendRequest::TypeName = "FriendRequest";
}