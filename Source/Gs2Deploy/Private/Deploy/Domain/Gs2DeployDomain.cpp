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

#include "Deploy/Domain/Gs2Deploy.h"
#include "Deploy/Domain/Model/Stack.h"
#include "Deploy/Domain/Model/Resource.h"
#include "Deploy/Domain/Model/Event.h"
#include "Deploy/Domain/Model/Output.h"
#include "Core/Domain/Gs2.h"

namespace Gs2::Deploy::Domain
{

    FGs2DeployDomain::FGs2DeployDomain(
        const Core::Domain::FGs2Ptr& Gs2
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Client(MakeShared<Gs2::Deploy::FGs2DeployRestClient>(Gs2->RestSession)),
        ParentKey("deploy")
    {
    }

    FGs2DeployDomain::FGs2DeployDomain(
        const FGs2DeployDomain& From
    ):
        Gs2(From.Gs2),
        Client(From.Client),
        ParentKey(From.ParentKey)
    {

    }

    FGs2DeployDomain::FCreateStackTask::FCreateStackTask(
        const TSharedPtr<FGs2DeployDomain>& Self,
        const Request::FCreateStackRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2DeployDomain::FCreateStackTask::FCreateStackTask(
        const FCreateStackTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2DeployDomain::FCreateStackTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Deploy::Domain::Model::FStackDomain>> Result
    )
    {
        const auto Future = Self->Client->CreateStack(
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
                const auto ParentKey = FString("deploy:Stack");
                const auto Key = Gs2::Deploy::Domain::Model::FStackDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Deploy::Model::FStack::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::Deploy::Domain::Model::FStackDomain>(
            Self->Gs2,
            Self,
            ResultModel->GetItem()->GetName()
        );
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2DeployDomain::FCreateStackTask>> FGs2DeployDomain::CreateStack(
        Request::FCreateStackRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateStackTask>>(this->AsShared(), Request);
    }

    FGs2DeployDomain::FCreateStackFromGitHubTask::FCreateStackFromGitHubTask(
        const TSharedPtr<FGs2DeployDomain>& Self,
        const Request::FCreateStackFromGitHubRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2DeployDomain::FCreateStackFromGitHubTask::FCreateStackFromGitHubTask(
        const FCreateStackFromGitHubTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2DeployDomain::FCreateStackFromGitHubTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Deploy::Domain::Model::FStackDomain>> Result
    )
    {
        const auto Future = Self->Client->CreateStackFromGitHub(
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
                const auto ParentKey = FString("deploy:Stack");
                const auto Key = Gs2::Deploy::Domain::Model::FStackDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Deploy::Model::FStack::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::Deploy::Domain::Model::FStackDomain>(
            Self->Gs2,
            Self,
            ResultModel->GetItem()->GetName()
        );
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2DeployDomain::FCreateStackFromGitHubTask>> FGs2DeployDomain::CreateStackFromGitHub(
        Request::FCreateStackFromGitHubRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateStackFromGitHubTask>>(this->AsShared(), Request);
    }

    FGs2DeployDomain::FValidateTask::FValidateTask(
        const TSharedPtr<FGs2DeployDomain>& Self,
        const Request::FValidateRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2DeployDomain::FValidateTask::FValidateTask(
        const FValidateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2DeployDomain::FValidateTask::Action(
        TSharedPtr<TSharedPtr<FGs2DeployDomain>> Result
    )
    {
        const auto Future = Self->Client->Validate(
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
            
        }
        const auto Domain = Self;
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2DeployDomain::FValidateTask>> FGs2DeployDomain::Validate(
        Request::FValidateRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FValidateTask>>(this->AsShared(), Request);
    }

    Gs2::Deploy::Domain::Iterator::FDescribeStacksIteratorPtr FGs2DeployDomain::Stacks(
    ) const
    {
        return MakeShared<Gs2::Deploy::Domain::Iterator::FDescribeStacksIterator>(
            Gs2->Cache,
            Client
        );
    }

    Gs2::Core::Domain::CallbackID FGs2DeployDomain::SubscribeStacks(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Deploy::Model::FStack::TypeName,
            "deploy:Stack",
            Callback
        );
    }

    void FGs2DeployDomain::UnsubscribeStacks(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Deploy::Model::FStack::TypeName,
            "deploy:Stack",
            CallbackID
        );
    }

    TSharedPtr<Gs2::Deploy::Domain::Model::FStackDomain> FGs2DeployDomain::Stack(
        const FString StackName
    )
    {
        return MakeShared<Gs2::Deploy::Domain::Model::FStackDomain>(
            Gs2,
            AsShared(),
            StackName == TEXT("") ? TOptional<FString>() : TOptional<FString>(StackName)
        );
    }

    void FGs2DeployDomain::UpdateCacheFromStampSheet(
        const FString Method,
        const FString Request,
        const FString Result
    ) {
    }

    void FGs2DeployDomain::UpdateCacheFromStampTask(
        const FString Method,
        const FString Request,
        const FString Result
    ) {
    }

    void FGs2DeployDomain::UpdateCacheFromJobResult(
        const FString Method,
        const Gs2::JobQueue::Model::FJobPtr Job,
        const Gs2::JobQueue::Model::FJobResultBodyPtr Result
    ) {
    }

    void FGs2DeployDomain::HandleNotification(
        const FString Action,
        const FString Payload
    ) {
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

