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

#include "Deploy/Domain/Model/Resource.h"
#include "Deploy/Domain/Model/Stack.h"
#include "Deploy/Domain/Model/Resource.h"
#include "Deploy/Domain/Model/Event.h"
#include "Deploy/Domain/Model/Output.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Deploy::Domain::Model
{

    FResourceDomain::FResourceDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> StackName,
        const TOptional<FString> ResourceName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Deploy::FGs2DeployRestClient>(Session)),
        StackName(StackName),
        ResourceName(ResourceName),
        ParentKey(Gs2::Deploy::Domain::Model::FStackDomain::CreateCacheParentKey(
            StackName,
            "Resource"
        ))
    {
    }

    FResourceDomain::FResourceDomain(
        const FResourceDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FResourceDomain::FGetTask::FGetTask(
        const TSharedPtr<FResourceDomain> Self,
        const Request::FGetResourceRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FResourceDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FResourceDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Deploy::Model::FResource>> Result
    )
    {
        Request
            ->WithStackName(Self->StackName)
            ->WithResourceName(Self->ResourceName);
        const auto Future = Self->Client->GetResource(
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
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Deploy::Domain::Model::FStackDomain::CreateCacheParentKey(
                    Self->StackName,
                    "Resource"
                );
                const auto Key = Gs2::Deploy::Domain::Model::FResourceDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Deploy::Model::FResource::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FResourceDomain::FGetTask>> FResourceDomain::Get(
        Request::FGetResourceRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FResourceDomain::CreateCacheParentKey(
        TOptional<FString> StackName,
        TOptional<FString> ResourceName,
        FString ChildType
    )
    {
        return FString() +
            (StackName.IsSet() ? *StackName : "null") + ":" +
            (ResourceName.IsSet() ? *ResourceName : "null") + ":" +
            ChildType;
    }

    FString FResourceDomain::CreateCacheKey(
        TOptional<FString> ResourceName
    )
    {
        return FString() +
            (ResourceName.IsSet() ? *ResourceName : "null");
    }

    FResourceDomain::FModelTask::FModelTask(
        const TSharedPtr<FResourceDomain> Self
    ): Self(Self)
    {

    }

    FResourceDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FResourceDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Deploy::Model::FResource>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Deploy::Model::FResource> Value;
        auto bCacheHit = Self->Cache->TryGet<Gs2::Deploy::Model::FResource>(
            Self->ParentKey,
            Gs2::Deploy::Domain::Model::FResourceDomain::CreateCacheKey(
                Self->ResourceName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Deploy::Request::FGetResourceRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Deploy::Domain::Model::FResourceDomain::CreateCacheKey(
                    Self->ResourceName
                );
                Self->Cache->Put(
                    Gs2::Deploy::Model::FResource::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "resource")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Cache->TryGet<Gs2::Deploy::Model::FResource>(
                Self->ParentKey,
                Gs2::Deploy::Domain::Model::FResourceDomain::CreateCacheKey(
                    Self->ResourceName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FResourceDomain::FModelTask>> FResourceDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FResourceDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

