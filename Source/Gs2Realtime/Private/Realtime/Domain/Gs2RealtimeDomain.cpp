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

// ReSharper disable CppUnusedIncludeDirective

#include "Realtime/Domain/Gs2Realtime.h"
#include "Realtime/Domain/Model/Namespace.h"
#include "Realtime/Domain/Model/Room.h"
#include "Core/Domain/Gs2.h"

namespace Gs2::Realtime::Domain
{

    FGs2RealtimeDomain::FGs2RealtimeDomain(
        const Core::Domain::FGs2Ptr Gs2
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Client(MakeShared<Gs2::Realtime::FGs2RealtimeRestClient>(Gs2->RestSession)),
        ParentKey("realtime")
    {
    }

    FGs2RealtimeDomain::FGs2RealtimeDomain(
        const FGs2RealtimeDomain& From
    ):
        Gs2(From.Gs2),
        Client(From.Client),
        ParentKey(From.ParentKey)
    {

    }

    FGs2RealtimeDomain::FCreateNamespaceTask::FCreateNamespaceTask(
        TSharedPtr<FGs2RealtimeDomain> Self,
        const Request::FCreateNamespaceRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2RealtimeDomain::FCreateNamespaceTask::FCreateNamespaceTask(
        const FCreateNamespaceTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2RealtimeDomain::FCreateNamespaceTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Realtime::Domain::Model::FNamespaceDomain>> Result
    )
    {
        const auto Future = Self->Client->CreateNamespace(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            {
                const auto ParentKey = FString("realtime:Namespace");
                const auto Key = Gs2::Realtime::Domain::Model::FNamespaceDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Realtime::Model::FNamespace::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::Realtime::Domain::Model::FNamespaceDomain>(
            Self->Gs2,
            ResultModel->GetItem()->GetName()
        );
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2RealtimeDomain::FCreateNamespaceTask>> FGs2RealtimeDomain::CreateNamespace(
        Request::FCreateNamespaceRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateNamespaceTask>>(this->AsShared(), Request);
    }

    Gs2::Realtime::Domain::Iterator::FDescribeNamespacesIteratorPtr FGs2RealtimeDomain::Namespaces(
    ) const
    {
        return MakeShared<Gs2::Realtime::Domain::Iterator::FDescribeNamespacesIterator>(
            Gs2->Cache,
            Client
        );
    }

    Gs2::Core::Domain::CallbackID FGs2RealtimeDomain::SubscribeNamespaces(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Realtime::Model::FNamespace::TypeName,
            "realtime:Namespace",
            Callback
        );
    }

    void FGs2RealtimeDomain::UnsubscribeNamespaces(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Realtime::Model::FNamespace::TypeName,
            "realtime:Namespace",
            CallbackID
        );
    }

    TSharedPtr<Gs2::Realtime::Domain::Model::FNamespaceDomain> FGs2RealtimeDomain::Namespace(
        const FString NamespaceName
    ) const
    {
        return MakeShared<Gs2::Realtime::Domain::Model::FNamespaceDomain>(
            Gs2,
            NamespaceName == TEXT("") ? TOptional<FString>() : TOptional<FString>(NamespaceName)
        );
    }

    void FGs2RealtimeDomain::UpdateCacheFromStampSheet(
        const FString Method,
        const FString Request,
        const FString Result
    ) {
    }

    void FGs2RealtimeDomain::UpdateCacheFromStampTask(
        const FString Method,
        const FString Request,
        const FString Result
    ) {
    }

    void FGs2RealtimeDomain::UpdateCacheFromJobResult(
        const FString Method,
        const Gs2::JobQueue::Model::FJobPtr Job,
        const Gs2::JobQueue::Model::FJobResultBodyPtr Result
    ) {
    }

    void FGs2RealtimeDomain::HandleNotification(
        const FString Action,
        const FString Payload
    ) {
        if (Action == "Create") {
            TSharedPtr<FJsonObject> PayloadJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Payload);
                !FJsonSerializer::Deserialize(JsonReader, PayloadJson))
            {
                return;
            }
            CreateNotificationEvent.Broadcast(Gs2::Realtime::Model::FCreateNotification::FromJson(PayloadJson));
        }
    }

    FCreateNotificationEvent& FGs2RealtimeDomain::OnCreateNotification()
    {
        return CreateNotificationEvent;
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

