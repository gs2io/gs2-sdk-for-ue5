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

#include "Distributor/Domain/Gs2Distributor.h"
#include "Distributor/Domain/Model/Namespace.h"
#include "Distributor/Domain/Model/DistributorModelMaster.h"
#include "Distributor/Domain/Model/DistributorModel.h"
#include "Distributor/Domain/Model/CurrentDistributorMaster.h"
#include "Distributor/Domain/Model/Distribute.h"
#include "Distributor/Domain/Model/User.h"
#include "Distributor/Domain/Model/UserAccessToken.h"
#include "Distributor/Domain/Model/StampSheetResult.h"

namespace Gs2::Distributor::Domain
{

    FGs2DistributorDomain::FGs2DistributorDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session
        // ReSharper disable once CppMemberInitializersOrder
    ):
        CompletedStampSheets(MakeShared<TArray<Gs2::Distributor::Model::FAutoRunStampSheetNotificationPtr>>()),
        CompletedStampSheetsMutex(MakeShared<FCriticalSection>()),
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Distributor::FGs2DistributorRestClient>(Session)),
        ParentKey("distributor")
    {
    }

    FGs2DistributorDomain::FGs2DistributorDomain(
        const FGs2DistributorDomain& From
    ):
        CompletedStampSheets(From.CompletedStampSheets),
        CompletedStampSheetsMutex(From.CompletedStampSheetsMutex),
        AutoRunStampSheetNotificationEvent(From.AutoRunStampSheetNotificationEvent),
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client),
        ParentKey(From.ParentKey)
    {

    }

    FGs2DistributorDomain::FCreateNamespaceTask::FCreateNamespaceTask(
        TSharedPtr<FGs2DistributorDomain> Self,
        const Request::FCreateNamespaceRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2DistributorDomain::FCreateNamespaceTask::FCreateNamespaceTask(
        const FCreateNamespaceTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2DistributorDomain::FCreateNamespaceTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Distributor::Domain::Model::FNamespaceDomain>> Result
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
                const auto ParentKey = FString("distributor:Namespace");
                const auto Key = Gs2::Distributor::Domain::Model::FNamespaceDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Distributor::Model::FNamespace::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::Distributor::Domain::Model::FNamespaceDomain>(
            Self->Cache,
            Self->JobQueueDomain,
            Self->StampSheetConfiguration,
            Self->Session,
            ResultModel->GetItem()->GetName()
        );
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2DistributorDomain::FCreateNamespaceTask>> FGs2DistributorDomain::CreateNamespace(
        Request::FCreateNamespaceRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateNamespaceTask>>(this->AsShared(), Request);
    }

    Gs2::Distributor::Domain::Iterator::FDescribeNamespacesIteratorPtr FGs2DistributorDomain::Namespaces(
    ) const
    {
        return MakeShared<Gs2::Distributor::Domain::Iterator::FDescribeNamespacesIterator>(
            Cache,
            Client
        );
    }

    TSharedPtr<Gs2::Distributor::Domain::Model::FNamespaceDomain> FGs2DistributorDomain::Namespace(
        const FString NamespaceName
    ) const
    {
        return MakeShared<Gs2::Distributor::Domain::Model::FNamespaceDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName == TEXT("") ? TOptional<FString>() : TOptional<FString>(NamespaceName)
        );
    }

    void FGs2DistributorDomain::UpdateCacheFromStampSheet(
        const FString Method,
        const FString Request,
        const FString Result
    ) {
    }

    void FGs2DistributorDomain::UpdateCacheFromStampTask(
        const FString Method,
        const FString Request,
        const FString Result
    ) {
    }

    void FGs2DistributorDomain::UpdateCacheFromJobResult(
        const FString Method,
        const Gs2::JobQueue::Model::FJobPtr Job,
        const Gs2::JobQueue::Model::FJobResultBodyPtr Result
    ) {
    }

    void FGs2DistributorDomain::HandleNotification(
        const FString Action,
        const FString Payload
    ) {
        if (Action == "AutoRunStampSheetNotification") {
            TSharedPtr<FJsonObject> PayloadJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Payload);
                !FJsonSerializer::Deserialize(JsonReader, PayloadJson))
            {
                return;
            }
            CompletedStampSheetsMutex->Lock();
            {
                const auto Notification = Gs2::Distributor::Model::FAutoRunStampSheetNotification::FromJson(PayloadJson);
                CompletedStampSheets->Add(Notification);
                AutoRunStampSheetNotificationEvent.Broadcast(Notification);
            }
            CompletedStampSheetsMutex->Unlock();
        }
    }

    FAutoRunStampSheetNotificationEvent& FGs2DistributorDomain::OnAutoRunStampSheetNotification()
    {
        return AutoRunStampSheetNotificationEvent;
    }

    FGs2DistributorDomain::FDispatchTask::FDispatchTask(
        const TSharedPtr<FGs2DistributorDomain> Self,
        const Gs2::Auth::Model::FAccessTokenPtr AccessToken
    ): Self(Self), AccessToken(AccessToken)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2DistributorDomain::FDispatchTask::Action(
        TSharedPtr<TSharedPtr<void*>> Result
    )
    {
        if (Self->CompletedStampSheetsMutex->TryLock())
        {
            TArray CopiedCompletedStampSheetsTemp(*Self->CompletedStampSheets);
            {
                if (Self->CompletedStampSheets->Num() == 0)
                {
                    return nullptr;
                }

                for (auto CompletedStampSheet : CopiedCompletedStampSheetsTemp)
                {
                    if (!CompletedStampSheet->GetTransactionId().IsSet())
                    {
                        continue;
                    }
                    const auto Future = MakeShared<Gs2::Core::Domain::Model::FAutoStampSheetDomain>(
                        Self->Cache,
                        Self->JobQueueDomain,
                        Self->Session,
                        AccessToken,
                        *CompletedStampSheet->GetNamespaceName(),
                        *CompletedStampSheet->GetTransactionId(),
                        Self->StampSheetConfiguration
                    )->Run();
                    Future->StartSynchronousTask();
                    if (Future->GetTask().IsError())
                    {
                        if (Future->GetTask().Error()->Type() == Gs2::Core::Model::FNotFoundError::TypeString)
                        {
                        }
                        else
                        {
                            return Future->GetTask().Error();
                        }
                    }
                    Future->EnsureCompletion();
                }

                Self->CompletedStampSheets->Reset();
            }
            Self->CompletedStampSheetsMutex->Unlock();
        }
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2DistributorDomain::FDispatchTask>> FGs2DistributorDomain::Dispatch(
        const Gs2::Auth::Model::FAccessTokenPtr AccessToken
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FGs2DistributorDomain::FDispatchTask>>(this->AsShared(), AccessToken);
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

