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
#include "Formation/Domain/Model/UserAccessToken.h"
#include "Formation/Model/Gs2FormationEzPropertyForm.h"
#include "Util/Net/GameSession.h"

namespace Gs2::UE5::Formation::Domain::Iterator
{

	class EZGS2_API FEzDescribePropertyFormsIterator :
        public TSharedFromThis<FEzDescribePropertyFormsIterator>
    {
        Gs2::Formation::Domain::Iterator::FDescribePropertyFormsIteratorPtr It;
        Gs2::Formation::Domain::Model::FUserAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::IGameSessionPtr GameSession;
        Gs2::UE5::Util::FGs2ConnectionPtr Connection;
        FString PropertyFormModelName;

	public:

        explicit FEzDescribePropertyFormsIterator(
            Gs2::Formation::Domain::Model::FUserAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::IGameSessionPtr GameSession,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection,
            FString PropertyFormModelName
        ) :
            It(
                Domain->PropertyForms(
                    PropertyFormModelName
                )
            ),
            Domain(Domain),
            GameSession(GameSession),
            Connection(Connection),
            PropertyFormModelName(PropertyFormModelName)
        {
        }

		FEzDescribePropertyFormsIterator(
			const FEzDescribePropertyFormsIterator& From
		) :
			It(From.It),
			Domain(From.Domain),
			GameSession(From.GameSession),
			Connection(From.Connection),
            PropertyFormModelName(From.PropertyFormModelName)
		{
		}

		class EZGS2_API FIterator
		{
		    friend class FEzDescribePropertyFormsIterator;

			Gs2::Formation::Domain::Iterator::FDescribePropertyFormsIterator::FIterator DomainIterator;
			Gs2::UE5::Formation::Model::FEzPropertyFormPtr CurrentValue;
        	static Gs2::UE5::Formation::Model::FEzPropertyFormPtr ConvertCurrent(
        		Gs2::Formation::Domain::Iterator::FDescribePropertyFormsIterator::FIterator& DomainIterator
        	)
        	{
				return DomainIterator.IsCurrentValid()
	    			? Gs2::UE5::Formation::Model::FEzPropertyForm::FromModel(DomainIterator.Current())
					: nullptr;
        	}

			explicit FIterator(
				Gs2::Formation::Domain::Iterator::FDescribePropertyFormsIterator::FIterator&& DomainIterator
			) :
			    DomainIterator(DomainIterator),
			    CurrentValue(ConvertCurrent(DomainIterator))
			{}

		public:
			explicit FIterator(
				FEzDescribePropertyFormsIterator& Iterable
			) :
			    FIterator(Iterable.begin())
			{}

			FIterator(
			    const FIterator& Iterator
            ) :
                DomainIterator(Iterator.DomainIterator),
                CurrentValue(Iterator.CurrentValue)
            {}

			FIterator& operator*()
			{
				return *this;
			}

			const FIterator& operator*() const
			{
				return *this;
			}

			FIterator* operator->()
			{
				return this;
			}

			const FIterator* operator->() const
			{
				return this;
			}

			FIterator& operator++()
			{
				++DomainIterator;
				CurrentValue = ConvertCurrent(DomainIterator);
				return *this;
			}
            Gs2::UE5::Formation::Model::FEzPropertyFormPtr& Current()
            {
                return CurrentValue;
            }

            Gs2::Core::Model::FGs2ErrorPtr Error()
            {
                return DomainIterator.Error();
            }

            bool IsError() const
            {
                return DomainIterator.IsError();
            }

            void Retry()
            {
                DomainIterator.Retry();
            }

			friend bool operator== (const FIterator& a, const FIterator& b)
			{
				return a.DomainIterator == b.DomainIterator;
			}
			friend bool operator!= (const FIterator& a, const FIterator& b)
			{
				return !operator==(a, b);
			}
		};

		FIterator OneBeforeBegin()
		{
			return FIterator(It->OneBeforeBegin());
		}
		FIterator begin()
		{
			return FIterator(It->begin());
		}
		FIterator end()
		{
			return FIterator(It->end());
		}
    };
	typedef TSharedPtr<FEzDescribePropertyFormsIterator> FEzDescribePropertyFormsIteratorPtr;
}
