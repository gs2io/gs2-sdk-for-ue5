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

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif


#include "Core/Domain/Model/NotificationMessage.h"
#include "Dom/JsonObject.h"

namespace Gs2::Core::Domain::Model
{
    FNotificationMessage::FNotificationMessage()
    {
    }

    FNotificationMessage::FNotificationMessage(
        const FNotificationMessage& From
    ): Issuer(From.Issuer), Subject(From.Subject), Payload(From.Payload)
    {
    }

    TSharedPtr<FNotificationMessage> FNotificationMessage::WithIssuer(const TOptional<FString> Issuer)
    {
        this->Issuer = Issuer;
        return this->AsShared();
    }

    TSharedPtr<FNotificationMessage> FNotificationMessage::WithSubject(const TOptional<FString> Subject)
    {
        this->Subject = Subject;
        return this->AsShared();
    }

    TSharedPtr<FNotificationMessage> FNotificationMessage::WithPayload(const TOptional<FString> Payload)
    {
        this->Payload = Payload;
        return this->AsShared();
    }

    TOptional<FString> FNotificationMessage::GetIssuer() const
    {
        return Issuer;
    }

    TOptional<FString> FNotificationMessage::GetSubject() const
    {
        return Subject;
    }

    TOptional<FString> FNotificationMessage::GetPayload() const
    {
        return Payload;
    }

    TSharedPtr<FNotificationMessage> FNotificationMessage::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FNotificationMessage>()
            ->WithIssuer(Data->HasField(ANSI_TO_TCHAR("issuer")) ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("issuer"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithSubject(Data->HasField(ANSI_TO_TCHAR("subject")) ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("subject"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithPayload(Data->HasField(ANSI_TO_TCHAR("payload")) ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("payload"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

