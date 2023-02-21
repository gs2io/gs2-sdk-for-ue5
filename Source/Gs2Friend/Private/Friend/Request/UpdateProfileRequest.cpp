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

#include "Friend/Request/UpdateProfileRequest.h"

namespace Gs2::Friend::Request
{
    FUpdateProfileRequest::FUpdateProfileRequest():
        NamespaceNameValue(TOptional<FString>()),
        AccessTokenValue(TOptional<FString>()),
        PublicProfileValue(TOptional<FString>()),
        FollowerProfileValue(TOptional<FString>()),
        FriendProfileValue(TOptional<FString>())
    {
    }

    FUpdateProfileRequest::FUpdateProfileRequest(
        const FUpdateProfileRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        AccessTokenValue(From.AccessTokenValue),
        PublicProfileValue(From.PublicProfileValue),
        FollowerProfileValue(From.FollowerProfileValue),
        FriendProfileValue(From.FriendProfileValue)
    {
    }

    TSharedPtr<FUpdateProfileRequest> FUpdateProfileRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateProfileRequest> FUpdateProfileRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateProfileRequest> FUpdateProfileRequest::WithAccessToken(
        const TOptional<FString> AccessToken
    )
    {
        this->AccessTokenValue = AccessToken;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateProfileRequest> FUpdateProfileRequest::WithPublicProfile(
        const TOptional<FString> PublicProfile
    )
    {
        this->PublicProfileValue = PublicProfile;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateProfileRequest> FUpdateProfileRequest::WithFollowerProfile(
        const TOptional<FString> FollowerProfile
    )
    {
        this->FollowerProfileValue = FollowerProfile;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateProfileRequest> FUpdateProfileRequest::WithFriendProfile(
        const TOptional<FString> FriendProfile
    )
    {
        this->FriendProfileValue = FriendProfile;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateProfileRequest> FUpdateProfileRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FUpdateProfileRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FUpdateProfileRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FUpdateProfileRequest::GetAccessToken() const
    {
        return AccessTokenValue;
    }

    TOptional<FString> FUpdateProfileRequest::GetPublicProfile() const
    {
        return PublicProfileValue;
    }

    TOptional<FString> FUpdateProfileRequest::GetFollowerProfile() const
    {
        return FollowerProfileValue;
    }

    TOptional<FString> FUpdateProfileRequest::GetFriendProfile() const
    {
        return FriendProfileValue;
    }

    TOptional<FString> FUpdateProfileRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FUpdateProfileRequest> FUpdateProfileRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUpdateProfileRequest>()
            ->WithContextStack(Data->HasField("contextStack") ? TOptional<FString>(Data->GetStringField("contextStack")) : TOptional<FString>())
            ->WithNamespaceName(Data->HasField("namespaceName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("namespaceName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithAccessToken(Data->HasField("xGs2AccessToken") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("xGs2AccessToken", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithPublicProfile(Data->HasField("publicProfile") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("publicProfile", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithFollowerProfile(Data->HasField("followerProfile") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("followerProfile", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithFriendProfile(Data->HasField("friendProfile") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("friendProfile", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithDuplicationAvoider(Data->HasField("duplicationAvoider") ? TOptional<FString>(Data->GetStringField("duplicationAvoider")) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FUpdateProfileRequest::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ContextStackValue.IsSet())
        {
            JsonRootObject->SetStringField("contextStack", ContextStackValue.GetValue());
        }
        if (NamespaceNameValue.IsSet())
        {
            JsonRootObject->SetStringField("namespaceName", NamespaceNameValue.GetValue());
        }
        if (AccessTokenValue.IsSet())
        {
            JsonRootObject->SetStringField("xGs2AccessToken", AccessTokenValue.GetValue());
        }
        if (PublicProfileValue.IsSet())
        {
            JsonRootObject->SetStringField("publicProfile", PublicProfileValue.GetValue());
        }
        if (FollowerProfileValue.IsSet())
        {
            JsonRootObject->SetStringField("followerProfile", FollowerProfileValue.GetValue());
        }
        if (FriendProfileValue.IsSet())
        {
            JsonRootObject->SetStringField("friendProfile", FriendProfileValue.GetValue());
        }
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField("duplicationAvoider", DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}